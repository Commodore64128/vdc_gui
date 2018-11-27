// ====================================================================================
// vdc_win.h
//
// Lower-level functions and definitions which allow for a windowing UI on the Commodore 128
// Programs should not call these functions directly.
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_core.h"
#include <stdlib.h>

#ifndef _VDC_WIN_
#define _VDC_WIN_

#define VDC_WIN_BORDER_NONE 0
#define VDC_WIN_BORDER_LINE 1
#define VDC_WIN_BORDER_BLOCK 160

typedef struct Window WINDOW;
typedef struct Control WINCTRL;


struct Window
{
	BYTE x;
	BYTE y;
	BYTE width;
	BYTE height;
	BYTE border;
	BUFFER title;
	BUFFER frontBuffer;
	BUFFER backBuffer;
	WINCTRL *control;
};

struct Control
{
	BUFFER name;
	BYTE x;
	BYTE y;
	BYTE visible;
	BYTE controlType;
	void *sub;
	WINDOW *parentWindow;
	WINCTRL *prevControl;
	WINCTRL *nextControl;
	BYTE hasFocus;

	//Control specific handlers
	void (*RenderHandler)(WINCTRL *control);
	void (*InputHandler)(WINCTRL *control, BYTE key);
};


// Function Prototypes

void _renderWindowBorder(WINDOW *window);
void _renderUnderWindow(WINDOW *window);
void _restoreUnderWindow(WINDOW *window);
void _clearWindow(WINDOW *window);
void _renderWindowControls(WINDOW *window);

WINDOW* CreateWindow(BYTE row, BYTE col, BYTE width, BYTE height, BYTE border, BUFFER title);
void ShowWindow(WINDOW *window);
void RefreshWindow(WINDOW *window);
void CloseWindow(WINDOW *window);
void DestroyWindow(WINDOW *window);
void MoveWindow(WINDOW *window, BYTE row, BYTE col);
void ActivateWindow(WINDOW *window);

#endif