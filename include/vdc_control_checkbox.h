// ====================================================================================
// vdc_control_checkbox.h
//
// Code for checkbox control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_win.h"

#ifndef _VDC_CONTROL_CHECKBOX_
#define _VDC_CONTROL_CHECKBOX_

#define CONTROLTYPE_CHECKBOX	3

typedef struct _CHECKBOX CHECKBOX;

struct _CHECKBOX
{
	WINCTRL *base;
	BUFFER text;
	BYTE value;

	//Event delegates
	void (*OnChanged)(CHECKBOX *checkBox);
};

CHECKBOX* CreateCheckbox(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE *text);

void _renderCheckboxHandler(WINCTRL *control);
void _checkBoxInputHandler(WINCTRL *control, BYTE c);

#endif