// ====================================================================================
// vdc_controls.c
//
// Code for high level control management
//
// Code is released under the GPL
// Scott Hutter - 2010
//
// =====================================================================================

#include "vdc_gui.h"


WINCTRL* CreateControl(WINDOW *window, BUFFER name, BYTE x, BYTE y, int controlType)
{
	// Base control addition to a window.  Not much of a point in
	// calling this function directly, but its capitalized to simulate a 'public' method

	WINCTRL *ctrl = (WINCTRL *)malloc(sizeof(WINCTRL));
	WINCTRL *tmpctrl;
	
	if(ctrl == NULL)
		return NULL;

	if (window == NULL)
	{	free(ctrl);
		return NULL;
	}

	// The window structure contains the first control pointer
	// if this pointer is null, we set it to this new control
	// else, we loop through the controls (linked list) until we
	// find the end.
	if (window->control == NULL)
	{
		window->control = malloc(sizeof(WINCTRL));
		ctrl = window->control;
		ctrl->prevControl = NULL;
	}
	else
	{
		ctrl = window->control;

		while(ctrl->nextControl != NULL)
		{
			tmpctrl = ctrl;
			ctrl = ctrl->nextControl;
			ctrl->prevControl = tmpctrl;
		}

		ctrl->nextControl = malloc(sizeof(WINCTRL));
		ctrl = ctrl->nextControl;
	}

	ctrl->name = name;
	ctrl->x = x;
	ctrl->y = y;
	ctrl->visible = TRUE;
	ctrl->nextControl = NULL;
	ctrl->hasFocus = FALSE;

	ctrl->controlType = controlType;
	ctrl->parentWindow = window;

	
	
	return ctrl;
}




WINCTRL* FindControl(WINDOW *window, BUFFER name)
{
	WINCTRL* ctrl = window->control;

	while(ctrl != NULL)
	{
		if (strcmp(name, ctrl->name) == 0)
			return ctrl;
		else
			ctrl = ctrl->nextControl;
	}

	return NULL;
}

