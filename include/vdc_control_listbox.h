// ====================================================================================
// vdc_control_listbox.h
//
// Code for listbox control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_win.h"

#ifndef _VDC_CONTROL_LISTBOX_
#define _VDC_CONTROL_LISTBOX_

#define CONTROLTYPE_LISTBOX		4		//Should be unique across all controls

typedef struct _LISTBOX LISTBOX;
typedef struct _LISTITEM LISTITEM;

struct _LISTITEM
{
	BUFFER *text;
};

struct _LISTBOX
{
	WINCTRL *base;
	BYTE width;
	BYTE height;
	BYTE itemCount;
	BYTE selectedItem;
	LISTITEM *listitems;

	//Event delegates
	void (*OnChanged)(LISTBOX *listBox);
};

LISTBOX* CreateListbox(WINDOW *window, BUFFER name, BYTE x, BYTE y, BYTE width, BYTE height, BYTE itemCount, LISTITEM *listitems);

void _renderListBoxHandler(WINCTRL *control);


void _listBoxInputHandler(WINCTRL *control, BYTE c);

#endif