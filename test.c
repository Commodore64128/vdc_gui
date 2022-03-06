#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "vdc_gui.h"

void txtBox1_keyPressed(TEXTBOX *textBox, BYTE c);
void txtBox1_onEnter(TEXTBOX *textBox);
void btnOk_OnPressed(BUTTON *button);
void btnQuit_OnPressed(BUTTON *button);
void btnClose_OnPressed(BUTTON *button);

WINDOW *wHdr, *win1, *win2;

void main (void)
{
	TEXTBOX* txtBox1;
	TEXTBOX* txtBox2;
	CHECKBOX* chkBox1;
	BUTTON* btnOk;
	BUTTON* btnClose;
	LISTBOX* listBox1;

	BUTTON* btnQuit;

	DIR *fd;
    char name[]="*";
    struct dirent *mydir;
	//const char *liText[] = {"Item 1","Item 2","Item 3"}; 
	LISTITEM *listItems;
	BYTE fileCount;

	VDC_Init();

	// Set the background color to blue
	VDC_BackColor(VDC_BLACK);
	
	// Generate a background pattern
	VDC_Clear(VDC_PetsciiToScreenCode(0xE6));
	
	// Create the header window
	wHdr = CreateWindow(0, 0, 80, 3, VDC_WIN_BORDER_LINE, NULL);
	CreateLabel(wHdr, NULL, 2, 1, "VDC TUI File Manager Demo v1.0");
	
	// Create an input window
	win1 = CreateWindow(3,0,80,22,VDC_WIN_BORDER_LINE, "File Manager");

	//CreateLabel(win1,NULL,2,3,"Name:");
	//CreateLabel(win1, NULL, 2,5,"Age:");
	//txtBox1 = CreateTextbox(win1, "txtBox1", 8,3,10);
	//txtBox2 = CreateTextbox(win1, "txtBox2", 8,5,2);
	//chkBox1 = CreateCheckbox(win1, "chkBox1", 24,3, "Check me");

	CreateButton(win1, "BTN8", 2,2,"DRV 8");
	CreateButton(win1, "BTN9", 12,2,"DRV 9");
	CreateButton(win1, "BTN10",22,2,"DRV10");
	CreateButton(win1, "BTN11",32,2,"DRV11");
	
	listItems = (LISTITEM *)malloc(sizeof(LISTITEM));
	fileCount=0;

	fd = opendir(mydir);

	if(fd != NULL)
    {
        do
        {
            mydir = readdir(fd);
            if(mydir != 0)
            {
				if(mydir->d_type != _CBM_T_HEADER)
				{
					if(fileCount > 0)
						listItems = (LISTITEM *)realloc(listItems, sizeof(LISTITEM)*fileCount);
					
					listItems[fileCount].text = (BYTE *)malloc(sizeof(BYTE)*strlen(mydir->d_name)+1);
					strcpy(listItems[fileCount].text, mydir->d_name);
					printf("%s", listItems[fileCount].text);
					fileCount++;
				}
                //printf("%s%*s",mydir->d_name,16-strlen(mydir->d_name)," ");
            }
            else
                break;

        }while(1);
        closedir(fd);
    }
	
	//VDC_BackColor(VDC_BLACK);
	//VDC_Clear(32);
	//printf("\n%d,%s", fileCount, listItems[fileCount-1].text);
	//exit(0);
	
	listBox1 = CreateListbox(win1, "listBox1", 2, 3, 40, 15, fileCount, listItems);
	//btnOk = CreateButton(win1, NULL, 13,8,"Ok");
	//btnClose = CreateButton(win1, NULL, 22, 8, "Close");

	//Add callback to handle events
	//txtBox1->OnEnter = txtBox1_onEnter;
	//btnOk->OnPressed = btnOk_OnPressed;
	//btnClose->OnPressed = btnClose_OnPressed;
	//btnQuit->OnPressed = btnQuit_OnPressed;

	//Show the windows
	ShowWindow(wHdr);
	ShowWindow(win1);
	

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



