#include <stdio.h>
#include <string.h>

#include "vdc_gui.h"

void txtBox1_keyPressed(TEXTBOX *textBox, BYTE c);
void txtBox1_onEnter(TEXTBOX *textBox);
void btnOk_OnPressed(BUTTON *button);
void btnQuit_OnPressed(BUTTON *button);
void btnClose_OnPressed(BUTTON *button);

WINDOW *win1, *win2;

void main (void)
{
	TEXTBOX* txtBox1;
	TEXTBOX* txtBox2;
	CHECKBOX* chkBox1;
	BUTTON* btnOk;
	BUTTON* btnClose;
	LISTBOX* listBox1;

	BUTTON* btnQuit;

	VDC_Init();

	// Set the background color to blue
	VDC_BackColor(VDC_DBLUE);
	
	// Generate a background pattern
	VDC_Clear(VDC_PetsciiToScreenCode(0xE6));
	
	// Create the header window
	win2 = CreateWindow(1, 4, 70, 5, VDC_WIN_BORDER_LINE, NULL);
	CreateLabel(win2, NULL, 2, 2, "This is a demo of the VDC GUI library.");
	btnQuit = CreateButton(win2, NULL, 40, 3, "Quit");
	
	// Create an input window
	win1 = CreateWindow(7,5,55,10,VDC_WIN_BORDER_LINE, "Input Test");

	CreateLabel(win1,NULL,2,3,"Name:");
	CreateLabel(win1, NULL, 2,5,"Age:");
	txtBox1 = CreateTextbox(win1, "txtBox1", 8,3,10);
	txtBox2 = CreateTextbox(win1, "txtBox2", 8,5,2);
	chkBox1 = CreateCheckbox(win1, "chkBox1", 24,3, "Check me");
	listBox1 = CreateListbox(win1, "listBox1", 38, 3, 9, 6, 3, "Item1,Item2,Item3");
	btnOk = CreateButton(win1, NULL, 13,8,"Ok");
	btnClose = CreateButton(win1, NULL, 22, 8, "Close");

	//Add callback to handle events
	txtBox1->OnEnter = txtBox1_onEnter;
	btnOk->OnPressed = btnOk_OnPressed;
	btnClose->OnPressed = btnClose_OnPressed;
	btnQuit->OnPressed = btnQuit_OnPressed;

	//Show the windows
	ShowWindow(win1);
	ShowWindow(win2);

	// Begin message processing
	ActivateWindow(win1);
}

void txtBox1_onEnter(TEXTBOX *textBox)
{
	WINDOW *currentWindow = textBox->base->parentWindow;
	char text[30] = "hello ";

	strcat(text, textBox->text); 

	CreateLabel(currentWindow, NULL, 2,8, text);
	RefreshWindow(currentWindow);
}

void btnOk_OnPressed(BUTTON *button)
{
	char text[30] = "hello ";
	char *check = "checked";
	char *ncheck = "not checked";

	WINDOW *win = button->base->parentWindow;

	TEXTBOX* txtBox1 = (TEXTBOX *)(FindControl(win, "txtBox1")->sub);
	CHECKBOX* checkBox1 = (CHECKBOX *)(FindControl(win, "chkBox1")->sub);

	if (txtBox1 != NULL)
	{
		strcat(text, txtBox1->text); 

		CreateLabel(win2, NULL, 2,3, text);

		if(checkBox1->value == TRUE)
			CreateLabel(win2, NULL, 20, 3, check);
		else
			CreateLabel(win2, NULL, 20, 3, ncheck);

		RefreshWindow(win2);

		DestroyWindow(button->base->parentWindow);

		ActivateWindow(win2);
	}

}

void btnClose_OnPressed(BUTTON *button)
{
	DestroyWindow(win1);

	ActivateWindow(win2);
}

void btnQuit_OnPressed(BUTTON *button)
{
	DestroyWindow(win2);

	VDC_BackColor(VDC_BLACK);
	VDC_Clear(32);

	printf("Thank you for checking this project out.  Please feel free to submit pull requests and improve on the library!");

	exit(0);
}



