// ====================================================================================
// vdc_menus.h
//
// Code for menu control management (work in progress)
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#ifndef _VDC_MENUS_
#define _VDC_MENUS_

// Function Prototypes

WINDOW *CreateMenu(BYTE row, BYTE col, BYTE width, BYTE menuitemscount, char** menuitems);
char *DoMenu(WINDOW *window);


#endif