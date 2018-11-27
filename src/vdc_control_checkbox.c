// ====================================================================================
// vdc_control_checkbox.c
//
// Code for checkbox control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"

CHECKBOX* CreateCheckbox(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE *text)
{
	/* Adds a checkbox control to a window. */

	WINCTRL *ctrl;
	CHECKBOX *checkBox;

	ctrl = CreateControl(window, name,x,y, CONTROLTYPE_CHECKBOX);

	if (ctrl != NULL)
	{
		checkBox = malloc(sizeof(struct _CHECKBOX));
		
		//Set the pointers to simulate inheritance
		ctrl->sub = checkBox;
		checkBox->base = ctrl;

		//Set base handlers
		ctrl->RenderHandler = _renderCheckboxHandler;
		ctrl->InputHandler = _checkBoxInputHandler;

		//Set defaults
		checkBox->value = FALSE;
		checkBox->text = text;
		checkBox->OnChanged = NULL;

		return checkBox;
	}
	else
		return NULL;
}

void _renderCheckboxHandler(WINCTRL *ctrl)
{
	CHECKBOX *checkBox = (CHECKBOX *)ctrl->sub;
	WINDOW *window = checkBox->base->parentWindow;

	BYTE c;
	int i = 0;

	/* Get the address to place the control */
	int addr = VDC_RowColToAddress(window->y + ctrl->y, window->x + ctrl->x);

	/* Get the farthest right-hand border that we can place text */
	int maxAddr = VDC_RowColToAddress(window->y + ctrl->y, window->x + window->width - 4);

	if(window->border != VDC_WIN_BORDER_NONE)
		maxAddr--;

	if(ctrl->hasFocus)
		VDC_Poke(addr-1, VDC_PetsciiToScreenCode('*'));
	else
		VDC_Poke(addr-1, VDC_PetsciiToScreenCode(' '));

	VDC_Poke(addr++, VDC_PetsciiToScreenCode('['));

	if(checkBox->value == 1)
		VDC_Poke(addr++, VDC_PetsciiToScreenCode(250));
	else
		VDC_Poke(addr++, VDC_PetsciiToScreenCode(' '));

	VDC_Poke(addr++, VDC_PetsciiToScreenCode(']'));
	VDC_Poke(addr++, VDC_PetsciiToScreenCode(' '));

	/* Write the text */
	while( (c = *(checkBox->text+i++)) != 0)
		if(addr < maxAddr)
			VDC_Poke(addr++, VDC_PetsciiToScreenCode(c));
}


void _checkBoxInputHandler(WINCTRL *ctrl, BYTE c)
{
	CHECKBOX *checkBox = (CHECKBOX *)ctrl->sub;
	unsigned char buf[2]; 
	
	buf[0] = 250;
	buf[1] = 0;
	
	if(c == 32)
	{	
		WINCTRL *ctrl = checkBox->base;

		int x = 0;
		int y = 0;

		x = ctrl->parentWindow->x + ctrl->x;
		y = ctrl->parentWindow->y + ctrl->y;

		if (checkBox->value == TRUE)
		{
			checkBox->value = FALSE;
			VDC_PrintAt(y, x + 1, " ", 0);
		}
		else
		{
			checkBox->value = TRUE;
			VDC_PrintAt(y, x + 1, buf, 0);
		}
		
		// Handle custom events
		if(checkBox->OnChanged != NULL)
			checkBox->OnChanged(checkBox);
	}
}
