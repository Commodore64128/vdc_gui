// ====================================================================================
// vdc_control_button.c
//
// Code for button control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"

BUTTON* CreateButton(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE *text)
{
	/* Adds a button control to a window. */

	WINCTRL *ctrl;
	BUTTON *button;

	ctrl = CreateControl(window, name,x,y, CONTROLTYPE_BUTTON);

	if (ctrl != NULL)
	{
		button = malloc(sizeof(struct _BUTTON));
		
		//Set the pointers to simulate inheritance
		ctrl->sub = button;
		button->base = ctrl;

		//Set base handlers
		ctrl->RenderHandler = _renderButtonHandler;
		ctrl->InputHandler = _buttonInputHandler;

		//Set defaults
		button->text = text;
		button->OnPressed = NULL;

		return button;
	}
	else
		return NULL;
}


void _renderButtonHandler(WINCTRL *ctrl)
{
	BUTTON *button = (BUTTON *)ctrl->sub;
	WINDOW *window = button->base->parentWindow;
	
	BYTE c;
	int i = 0;

	/* Get the address to place the control */
	int addr = VDC_RowColToAddress(window->y + ctrl->y, window->x + ctrl->x);

	/* Get the farthest right-hand border that we can place text */
	int maxAddr = VDC_RowColToAddress(window->y + ctrl->y, window->x + window->width - 4);

	if(window->border != VDC_WIN_BORDER_NONE)
		maxAddr--;

	VDC_Poke(addr++, VDC_PetsciiToScreenCode('['));

	if(ctrl->hasFocus == TRUE)
		VDC_Poke(addr++, VDC_PetsciiToScreenCode('*'));
	else
		VDC_Poke(addr++, VDC_PetsciiToScreenCode(' '));

	/* Write the button text to the screen */
	while( (c = *(button->text+i++)) != 0)
		if(addr < maxAddr)
			VDC_Poke(addr++, VDC_PetsciiToScreenCode(c));

	VDC_Poke(addr++, VDC_PetsciiToScreenCode(' '));
	VDC_Poke(addr++, VDC_PetsciiToScreenCode(']'));

}

void _buttonInputHandler(WINCTRL *ctrl, BYTE c)
{
	BUTTON *button = (BUTTON *)ctrl->sub;

	if(c == 13)
		button->OnPressed(button);
}