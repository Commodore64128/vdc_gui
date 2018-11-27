// ====================================================================================
// vdc_control_textbox.h
//
// Code for textbox control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_win.h"

#ifndef _VDC_CONTROL_TEXTBOX_
#define _VDC_CONTROL_TEXTBOX_

#define CONTROLTYPE_TEXTBOX		1		//Should be unique across all controls

typedef struct _TEXTBOX TEXTBOX;

struct _TEXTBOX
{
	WINCTRL *base;
	BYTE maxLength;
	BUFFER text;
	int textPosition;

	//Event delegates
	void (*OnKeyPress)(TEXTBOX *textBox, BYTE c);
	void (*OnEnter)(TEXTBOX *textBox);
};

TEXTBOX* CreateTextbox(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE maxLength);

void _renderTextBoxHandler(WINCTRL *control);
void _textBoxInputHandler(WINCTRL *control, BYTE c);

#endif