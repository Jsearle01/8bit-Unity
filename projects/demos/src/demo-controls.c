
#include "unity.h"

extern const char keyNext, pressKeyMsg[];

#if defined __ORIC__
	const char* joyList[] = { "WASD+CTR", "IJKL+RET", "PASE/HUB 1", "PASE/HUB 2", "HUB 3" };
#elif defined __LYNX__
	const char* joyList[] = { "JOY 1", "HUB 1", "HUB 2", "HUB 3" };
#else 
	const char* joyList[] = { "JOY 1", "JOY 2", "JOY 3", "JOY 4" };
#endif

int DemoControls(void) 
{
	unsigned char i, *mou, joy, state[12];
	
	// Clear screen
	clrscr();
	
	//	Init joystick adapters
	InitJoy();
	
	// Print header
	gotoxy (8, 2);
	cprintf(pressKeyMsg);	
	gotoxy (7, 4);
	cprintf("MOUSE");	
	for (i=0; i<JOY_MAX; i++) {
		gotoxy (7, 6+2*i);
		cprintf(joyList[i]);
	}
	
	// Display joystick actions until 'SPACE' is pressed
	while (!kbhit () || cgetc () != keyNext) {
		// Display mouse state
		mou = GetMouse();
		gotoxy (18, 4); sprintf(state, "%u  ", mou[0], state); cprintf(state);
		gotoxy (23, 4); sprintf(state, "%u  ", mou[1], state); cprintf(state);
		strcpy(state, "   ");
		if (mou[2] & MOU_LEFT)   state[0] = 'L';
		if (mou[2] & MOU_MIDDLE) state[1] = 'M';
		if (mou[2] & MOU_RIGHT)  state[2] = 'R';
		gotoxy (28, 4); cprintf(state);
			
		// Display joystick states
		for (i=0; i<JOY_MAX; i++) {
			joy = GetJoy(i);
			memset(state, ' ', 11);
			if (joy & JOY_UP)    state[0] = 'U';
			if (joy & JOY_DOWN)  state[2] = 'D';
			if (joy & JOY_LEFT)  state[4] = 'L';
			if (joy & JOY_RIGHT) state[6] = 'R';
			if (joy & JOY_BTN1)  state[8] = 'A';
			if (joy & JOY_BTN2)  state[10] = 'B';
			gotoxy (19, 6+2*i);
			cprintf(state);
		}
	#if defined __LYNX__
		UpdateDisplay(); // Refresh Lynx screen
	#endif
	}
	
    // Done
    return EXIT_SUCCESS;	
}
