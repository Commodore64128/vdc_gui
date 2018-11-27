// ====================================================================================
// vdc_control_button.h
//
// Code for button control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_win.h"

#ifndef _VDC_CONTROL_BUTTON_
#define _VDC_CONTROL_BUTTON_

#define CONTROLTYPE_BUTTON		2		//Should be unique across all controls

typedef struct _BUTTON BUTTON;

struct _BUTTON
{
	WINCTRL *base;
	BUFFER text;

	//Event delegates
	void (*OnPressed)(BUTTON *button);
};

BUTTON* CreateButton(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE *text);

void _renderButtonHandler(WINCTRL *control);

void _buttonInputHandler(WINCTRL *control, BYTE c);

#endif
