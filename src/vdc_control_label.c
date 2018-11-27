// ====================================================================================
// vdc_control_label.c
//
// Code for label control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"

LABEL* CreateLabel(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE *text)
{
	/* Adds a label control to a window. */

	WINCTRL *ctrl;
	LABEL *label;

	ctrl = CreateControl(window, name, x,y, CONTROLTYPE_LABEL);

	if (ctrl != NULL)
	{
		label = malloc(sizeof(struct _LABEL));
		
		//Set the pointers to simulate inheritance
		ctrl->sub = label;
		label->base = ctrl;

		//Set base handlers
		ctrl->RenderHandler = _renderLabelHandler;
		ctrl->InputHandler = NULL;

		//Set values
		label->text = text;

		return label;
	}
	else
		return NULL;
}


void _renderLabelHandler(WINCTRL *ctrl)
{
	LABEL *label = (LABEL *)ctrl->sub;
	WINDOW *window = label->base->parentWindow;

	BYTE c;
	int i = 0;

	/* Get the address to place the control */
	int addr = VDC_RowColToAddress(window->y + ctrl->y, window->x + ctrl->x);

	/* Get the farthest right-hand border that we can place text */
	int maxAddr = VDC_RowColToAddress(window->y + ctrl->y, window->x + window->width);

	if(window->border != VDC_WIN_BORDER_NONE)
		maxAddr--;

	/* Write the text label to the screen */
	while( (c = *(label->text+i++)) != 0)
		if(addr < maxAddr)
			VDC_Poke(addr++, VDC_PetsciiToScreenCode(c));

}