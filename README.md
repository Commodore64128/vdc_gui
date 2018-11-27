# Commodore 128 VDC Text UI Library
Text UI for the Commodore 128 VDC.  
The library name current (incorrectly) implies this is a graphical user interface library.  

![Alt text](https://i.imgur.com/QxZuKw7.png "Screenshot")

Uses callbacks and high level object creation (pseudo object-oriented).

To create a window with some controls:

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
	
A sample is included.  The batch build files are for windows users (sorry, linux folks - no makefile yet).