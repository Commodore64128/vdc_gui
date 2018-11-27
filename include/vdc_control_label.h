// ====================================================================================
// vdc_control_label.h
//
// Code for label control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_win.h"

#ifndef _VDC_CONTROL_LABEL_
#define _VDC_CONTROL_LABEL_

#define CONTROLTYPE_LABEL		0		//Should be unique across all controls

typedef struct _LABEL LABEL;

struct _LABEL
{
	WINCTRL *base;
	BUFFER text;
};

LABEL* CreateLabel(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE *text);

void _renderLabelHandler(WINCTRL *control);

#endif

