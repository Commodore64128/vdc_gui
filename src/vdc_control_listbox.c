// ====================================================================================
// vdc_control_listbox.c
//
// Code for listbox control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"

LISTBOX* CreateListbox(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE width, BYTE height,  BYTE itemCount, LISTITEM *listitems)
{
	/* Adds a listBox control to a window. */

	WINCTRL *ctrl;
	LISTBOX *listBox;

	ctrl = CreateControl(window, name,x,y, CONTROLTYPE_LISTBOX);

	if (ctrl != NULL)
	{
		listBox = malloc(sizeof(struct _LISTBOX));
		
		//Set the pointers to simulate inheritance
		ctrl->sub = listBox;
		listBox->base = ctrl;

		//Set defaults
		listBox->width = width;
		listBox->height = height;
		listBox->listitems = listitems;
		listBox->itemCount = itemCount;
		listBox->selectedItem = 0;
		listBox->OnChanged = NULL;

		//Set handlers
		ctrl->RenderHandler = _renderListBoxHandler;
		ctrl->InputHandler = _listBoxInputHandler;

		return listBox;
	}
	else
		return NULL;
}

void _renderListBoxHandler(WINCTRL *ctrl)
{
	LISTBOX *listBox = (LISTBOX *)ctrl->sub;
	WINDOW *win = listBox->base->parentWindow;
	BYTE x;

	int col = win->x + ctrl->x;
	int row = win->y + ctrl->y;
	
	VDC_DrawBox(col, row, listBox->width, listBox->height, VDC_WIN_BORDER_LINE);

	row++;

	for (x=0; x < listBox->itemCount; x++)
	{
		if(listBox->selectedItem == x)
		{
			if(listBox->base->hasFocus == TRUE)
				VDC_PrintAt(row, col+1, "*", 1);
			else
				VDC_PrintAt(row, col+1, " ", 1);

			VDC_PrintAt(row++, col+2, (char *)listBox->listitems[x].text, 1);
		}
		else
		{
			VDC_PrintAt(row, col+1, " ", 0);
			VDC_PrintAt(row++, col+2, (char *)listBox->listitems[x].text, 0);
		}
	}
}


void _listBoxInputHandler(WINCTRL *ctrl, BYTE c)
{
	LISTBOX *listBox = (LISTBOX *)ctrl->sub;

	if(c == 17 && listBox->selectedItem < listBox->itemCount-1)
	{
		listBox->selectedItem++;
		_renderListBoxHandler(ctrl);

		if(listBox->OnChanged != NULL)
			listBox->OnChanged(listBox);
	}

	if(c == 145 && listBox->selectedItem > 0)
	{
		listBox->selectedItem--;
		_renderListBoxHandler(ctrl);

		if(listBox->OnChanged != NULL)
			listBox->OnChanged(listBox);
	}

	
}

