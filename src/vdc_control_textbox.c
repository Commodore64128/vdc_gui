// ====================================================================================
// vdc_control_textbox.c
//
// Code for textbox control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"


TEXTBOX* CreateTextbox(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE maxLength)
{
	/* Adds a textbox control to a window.  */

	WINCTRL *ctrl;
	TEXTBOX *textBox;
	int i = 0;

	ctrl = CreateControl(window, name, x,y, CONTROLTYPE_TEXTBOX);

	if (ctrl != NULL)
	{
		textBox = malloc(sizeof(struct _TEXTBOX));

		//Set the pointers to simulate inheritance
		textBox->base = ctrl;
		ctrl->sub = textBox;

		//Set base handlers
		ctrl->RenderHandler = _renderTextBoxHandler;
		ctrl->InputHandler = _textBoxInputHandler;
		
		//Set defaults
		textBox->maxLength = maxLength;
		textBox->textPosition = 0;
		textBox->text = malloc(sizeof(BYTE) * maxLength+1);

		textBox->OnEnter = NULL;
		textBox->OnKeyPress = NULL;

		//clear the buffer
		for(i = 0; i< textBox->maxLength+1; i++)
			textBox->text[i] = 0;

		return textBox;
	}
	else
		return NULL;
}

void _renderTextBoxHandler(WINCTRL *ctrl)
{
	TEXTBOX *textBox = (TEXTBOX *)ctrl->sub;
	WINDOW *window = textBox->base->parentWindow;

	int x = 0;
	int y = 0;
	int i = 0;

	/* Get the address to place the control */
	int addr = VDC_RowColToAddress(window->y + ctrl->y, window->x + ctrl->x);

	/* Get the farthest right-hand border that we can place text */
	int maxAddr = VDC_RowColToAddress(window->y + ctrl->y, window->x + window->width);

	if(window->border != VDC_WIN_BORDER_NONE)
		maxAddr--;

	/* Write the textbox to the screen */
	while(i++ <= textBox->maxLength)
		if(addr < maxAddr)
			VDC_Poke(addr++, VDC_PetsciiToScreenCode(160));

	x = ctrl->parentWindow->x + ctrl->x;
	y = ctrl->parentWindow->y + ctrl->y;

	//Print the current text in the buffer
	VDC_PrintAt(y, x, textBox->text, 1);

	if(ctrl->hasFocus == TRUE)
		VDC_PrintAt(y, x + textBox->textPosition, "*", 1);
	else
		VDC_PrintAt(y, x + textBox->textPosition, " ", 1);
}

void _textBoxInputHandler(WINCTRL *ctrl, BYTE c)
{
	TEXTBOX *textBox = (TEXTBOX *)ctrl->sub;

	if( (c > 31 && c < 128) && (textBox->textPosition < textBox->maxLength))
	{
		int x = 0;
		int y = 0;

		textBox->text[textBox->textPosition] = c;
		
		x = ctrl->parentWindow->x + ctrl->x;
		y = ctrl->parentWindow->y + ctrl->y;

		VDC_PrintAt(y, x, textBox->text, 1);

		VDC_PrintAt(y, x + textBox->textPosition + 1, "*", 1);

		// Handle custom events
		if (textBox->OnKeyPress != NULL)
			textBox->OnKeyPress(textBox, c);

	    textBox->textPosition++;
	}
	
	//Handle backspace key
	if(c == 20 && textBox->textPosition > 0)
	{
		int x = 0;
		int y = 0;

		x = ctrl->parentWindow->x + ctrl->x;
		y = ctrl->parentWindow->y + ctrl->y;

		VDC_PrintAt(y, x + textBox->textPosition, " ", 1);

		textBox->text[textBox->textPosition] = '\0';
		VDC_PrintAt(y, x, textBox->text, 1);

		VDC_PrintAt(y, x + textBox->textPosition - 1, "*", 1);

		// Handle custom events
		if (textBox->OnKeyPress != NULL)
			textBox->OnKeyPress(textBox, c);
		
		textBox->textPosition--;


	}

	//Handle return key
	if(c == 13 && textBox->OnEnter != NULL)
			textBox->OnEnter(textBox);

}