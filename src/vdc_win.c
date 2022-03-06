// ====================================================================================
// vdc_win.c
//
// Lower-level functions and definitions which allow for a windowing UI on the Commodore 128
// Programs should not call these functions directly.
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"

void _renderWindowBorder(WINDOW *window)
{
	if(window->border != VDC_WIN_BORDER_NONE)
		VDC_DrawBox(window->x, window->y, window->width, window->height, window->border);
}


void _renderWindowTitle(WINDOW *window)
{
	int addr, i, maxAddr;
	BYTE c;

	if(window->title != NULL)
	{
		/* Get the address to place the title */
		addr = VDC_RowColToAddress(window->y, window->x + 1);

		/* Get the farthest right-hand border that we can place text */
		maxAddr = VDC_RowColToAddress(window->y, window->x + window->width - 4);

		i = 0;

		VDC_Poke(addr++, VDC_PetsciiToScreenCode('['));
		VDC_Poke(addr++, VDC_PetsciiToScreenCode(' '));

		while( (c = *(window->title + i++)) != 0)
			if(addr < maxAddr)
				VDC_Poke(addr++, VDC_PetsciiToScreenCode(c));

		VDC_Poke(addr++, VDC_PetsciiToScreenCode(' '));
		VDC_Poke(addr++, VDC_PetsciiToScreenCode(']'));

	}
}

void _stashUnderWindow(WINDOW *window)
{
	int addr,t,i;

	/* Copy the underlying rectange */
	addr = VDC_RowColToAddress(window->y,window->x);

	t=0;
	for(i=0; i < window->height ; i++)
	{
		VDC_CopyVDCToMem(addr, (int)window->backBuffer + t, window->width);
		addr += 80;
		t += window->width;
	}
}

void _restoreUnderWindow(WINDOW *window)
{
	int addr,t,i;

	/* Resore the underlying rectange */
	addr = VDC_RowColToAddress(window->y,window->x);

	t = 0;
	for(i=0 ; i < window->height ; i++)
	{
		VDC_CopyMemToVDC((int)window->backBuffer + t, addr, window->width);
		addr += 80;
		t += window->width;
	}
}

void _clearWindow(WINDOW *window)
{
	int i,x;

	/* Clear the space for the window */
	for(i=0; i < window->height; i++)
		for(x=0; x < window->width; x++)
			VDC_Poke(VDC_RowColToAddress(window->y+i, window->x+x), 96);
}

void _renderWindowControls(WINDOW *window)
{
	WINCTRL *ctrl = window->control;

	while(ctrl != NULL)
	{
		if (ctrl->visible == TRUE)
			ctrl->RenderHandler(ctrl);

		ctrl = ctrl->nextControl;
	}
}

WINDOW* CreateWindow(BYTE row, BYTE col, BYTE width, BYTE height, BYTE border, BUFFER title)
{
	/* Creates a window (but doesnt display it).
	*
	*  Windows created must be closed or destroyed in the reverse order.
	*/

	WINDOW *window = (WINDOW *)malloc(sizeof(WINDOW));

	if(window == NULL)
		return NULL;

	/* Check dimensions */
	if((col + width > 80) || (row + height > 25)) 
		return NULL;

	/* Set the variables */
	window->x = col;
	window->y = row;
	window->width = width;
	window->height = height;
	window->border = border;
	window->control = NULL;
	window->title = title;

	/* Allocate the RAM for the window */
	if((window->frontBuffer = malloc((width * height) * sizeof(BYTE))) == NULL)
	{
		free(window);
		return NULL;
	}

	/* Allocate RAM to hold the data under a window */
	if((window->backBuffer = malloc((width * height) * sizeof(BYTE))) == NULL)
	{
		free(window->frontBuffer);
		free(window);
		return NULL;
	}

	return window;
}


void ShowWindow(WINDOW *window)
{
	if (window != NULL)
	{
		_stashUnderWindow(window);
		_clearWindow(window);
		_renderWindowBorder(window);
		_renderWindowTitle(window);
		_renderWindowControls(window);
	}
}

void RefreshWindow(WINDOW *window)
{
	if (window != NULL)
		_renderWindowControls(window);
}

void CloseWindow(WINDOW *window)
{
	if (window != NULL)
		_restoreUnderWindow(window);
}
void DestroyWindow(WINDOW *window)
{
	/* There is a bug here where the controls in the window 
	*  are not free()'ed.  Looked at this, and it looks like Ill need
	*  to implement a reverse-traversing (2-way) linked list, not singly linked.
	*  Otherwise I cant free() the memory.
	*/
	if (window != NULL)
	{
		CloseWindow(window);

		free(window->backBuffer);
		free(window->frontBuffer);
		free(window);
	}
}

void MoveWindow(WINDOW *window, BYTE row, BYTE col)
{
	CloseWindow(window);
	
	window->x = col;
	window->y = row;

	ShowWindow(window);

}




void ActivateWindow(WINDOW *window)
{
	WINCTRL *ctrl = window->control;  // control that has current focus
	int key=0;

	if(window->control == NULL)
		return;

	VDC_SetCursorMode(VDC_CURSORMODE_NONE);

	for(;;)
	{
		while(ctrl->InputHandler == NULL)
		{
			ctrl = ctrl->nextControl;
			
			//No controls to recieve focus. Quit program
			if (ctrl == NULL)
				ctrl = window->control;
		}

		//Clear keyboard buffer
		POKE(208,0);

		//Set the focus
		ctrl->hasFocus = TRUE;
		ctrl->RenderHandler(ctrl);

		// Wait for input
		for(;;)
		{
			//If CONTROL key is pressed, if(PEEK(211) == 4)
			
			key = kbhit();
		
			if(key != 0)
			{
				key = cgetc();
		
			//Has a keypress occurred?
			//if(PEEK(208) > 0)
			//{
			//	key = PEEK(842);

				//if F1 key, move to next control
				if(key == 133)
				{
					POKE(208,0);

					//Clear the focus
					ctrl->hasFocus = FALSE;
					ctrl->RenderHandler(ctrl);

					// if at end of control list, start back at top
					if((ctrl = ctrl->nextControl) == NULL)
						ctrl = window->control;
					break;
				}
				if(key == 134)
				{
					POKE(208,0);

					//Clear the focus
					ctrl->hasFocus = FALSE;
					ctrl->RenderHandler(ctrl);

					// if top of control list, go to last
					if(ctrl == window->control)
					{
						while(ctrl->nextControl != NULL) {
							ctrl = ctrl->nextControl;
						};
					}
					else
					{
						ctrl = ctrl->prevControl;
					}
					break;
				}

				ctrl->InputHandler(ctrl,key);

				POKE(208,0);
			}

		}

	}
}


