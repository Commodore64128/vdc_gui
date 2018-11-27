// ====================================================================================
// vdc_controls.h
//
// Code for high level control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_win.h"

#ifndef _VDC_CONTROLS_
#define _VDC_CONTROLS_

// Function Prototypes

WINCTRL* CreateControl(WINDOW *window, BUFFER name, BYTE x, BYTE y, int controlType);
WINCTRL* FindControl(WINDOW *window, BUFFER name);

#endif