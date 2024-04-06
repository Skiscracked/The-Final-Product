/*
 - Alternate screen code 
 - Screen resizing code
 - Change (limited number of vehicle characteristics)
 - Starts when a key is pressed on the KB

 - ECED 3401
 - 23 Oct 23
*/
#include "Emulation.h"

void screen_size()
{
/*
 - Query Windows for new window size
 - The screen (window) must be resized before this is called (see check_kb())
*/
CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;

/* Get new screen size */
GetConsoleScreenBufferInfo(scrout, &ScreenBufferInfo);

/* Erase existing diagnostic line */
CUP(1, scr_size.Y)
EL(scr_size.Y)

/* Get new screen size */
scr_size.X = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
scr_size.Y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;

/* Clear the screen */
CLRSCR

/* Resizing displays cursor - hide it */
printf(CSI "?25l");
}

void status_window()
{
	/*
	 - Switch to the status window (Alternate screen)
	 - Display v1 info
	 - Ask to change speed
	*/
	int val;



	/* Switch to Alternate screen */
	printf(CSI "?1049h");

	printf("In the Alternate screen");

	printf("How many AEDVs would you like to move? (Only from 1-4)\n");//Prompting the user for input
	(void)scanf("%d", &numofv);//scanning the users input, determining how many cars to create

	for (int i = 0; i < numofv; i++) {

		printf("What origin would you like to start from (x,y)?");
		(void)scanf("%d %d", &AEDV[i].origin.x, &AEDV[i].origin.y);
		printf("What destination would you like to end at (x,y)?");
		(void)scanf("%d %d", &AEDV[i].dest.x, &AEDV[i].dest.y);

	}

	//move( &y);



	/* Back to Main screen */
	printf(CSI "?1049l");

}

int check_kb()
{
/* 
 - Keystroke detected - check character
 - Return T/F:
   - T if '#' (end program)
   - F anything else
*/
int rc;
rc = (char)_getch();

switch (rc)
{
case 'R':
case 'r':
	/* resize screen - resizing the window must take place first */
	screen_size();
	populate_map();
	print_msg("Screen resized");
	rc = FALSE;
	break;

case '#':
	/* End */
	rc = TRUE;
	break;

default:
	/* Display vehicle status */
	status_window();
	rc = FALSE;
}

printf(CSI "?25l");	/* Hide cursor */
return rc;

}
