// ====================================================================================
// vdc_menus.c
//
// Code for menu control management (work in progress)
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"

WINDOW *CreateMenu(BYTE row, BYTE col, BYTE width, BYTE menuitemscount, char** menuitems)
{
	WINDOW *window;
	int i = 0;
	int ok = 0;

	window = CreateWindow(row,col,width,5,VDC_WIN_BORDER_LINE, NULL);

	if (ok == 0)
	{
		for(;i<menuitemscount;i++)
		{
			CreateLabel(window, NULL, 1,i+1,menuitems[i]);
		}
	}
	else
		return NULL;
}

char *DoMenu(WINDOW *window)
{
	return NULL;
}