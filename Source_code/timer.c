#include <MKL25Z4.H>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "timer.h"
#include "LCD_4bit.h"



void delayMs(int n);
void delayUs(int n);
void keypad_init(void);
char keypad_getkey(void);


/* create a delay function */
void Delay(volatile unsigned int time_del) {
	while (time_del--) {
		;
	}
}

void delayUs(int n)
{
    int i; int j;
    for(i = 0 ; i < n; i++) {
        for(j = 0; j < 5; j++) ;
    }
}





/*----------------------------------------------------------------------------
  Keypad Code
 *----------------------------------------------------------------------------*/


/* this function initializes PortC that is connected to the keypad.
 * All pins are configured as GPIO input pin with pull-up enabled.
 */

void keypad_init(void)
{
    SIM->SCGC5 |= 0x0800;       /* enable clock to Port C */
    SIM->SCGC5 |= 0x2000;       /* enable clock to Port E */
    
    PORTC->PCR[10] = 0x100;     /* make PTC10 pin as GPIO */
    PORTC->PCR[11] = 0x100;     /* make PTC11 pin as GPIO */
    PORTC->PCR[12] = 0x100;     /* make PTC12 pin as GPIO */
    PORTC->PCR[13] = 0x100;     /* make PTC13 pin as GPIO */
    
    PORTE->PCR[20] = 0x100;     /* make PTE20 pin as GPIO */
    PORTE->PCR[21] = 0x100;     /* make PTE21 pin as GPIO */
    PORTE->PCR[22] = 0x100;     /* make PTE22 pin as GPIO */
    PORTE->PCR[23] = 0x100;     /* make PTE23 pin as GPIO */
    
  //  PTC->PDDR &= ~(0xF << 10);  /* make PTC13-10 as inputs connected to rows */
  //  PTE->PDDR &= ~(0xF << 20);  /* make PTE23-20 as inputs connected to columns */
}

/*
 * This is a non-blocking function to read the keypad.
 * If a key is pressed, it returns a key code. Otherwise, a zero
 * is returned.
 * when the keys are not pressed, these pins are pull down LOW.
 * The Port E (PTE23-20) is used as output that drives the keypad cloumns.
 * First all rows are driven low and the input pins are read. If no
 * key is pressed, it will read as low at all rows. 
 * If any key is pressed, the program drives one column high at a time and 
 * leave the rest of the rows inactive (low) then read the output pins.
 * Knowing which row is active and which column is active, the program
 * can decide which key is pressed.
 */





char keypad_getkey(void)
{
    int row, col;
    const char col_select[] = {0x01, 0x02, 0x04, 0x08}; /* one row is active */
    const char keymap[] = " 123A456B789C0FED";
		
    /* check to see any key pressed first */
    PTE->PDDR |= 0xF << 20;             /* enable columns as outputs (PTE20-23)*/
    PTE->PSOR = 0xF << 20;              /* set column data pins all high in PDOR for PTE */
    delayUs(2);                         /* wait for signal to settle */
    row = (PTC->PDIR >> 10) & 0xF;      /* read all rows at PORT C (PTC10-13) */
    PTE->PCOR = 0xF << 20;              /* set column data pins all low */
    PTE->PDDR &= ~(0xF << 20);          /* disable all columns */

    if (row == 0) return 0;             /* no key pressed, return a zero */

    /* If a key is pressed, it gets here to find out which key.
     * It activates one row at a time and read the input to see
     * which column is active. */
		
    for (col = 0; col <= 4; col++)
    {
        PTE->PDDR &= ~(0xF << 20);          /* disable all cols */
        PTE->PDDR |= col_select[col] << 20; /* enable one col */
        PTE->PSOR = 0x0F << 20;             /* turn the active col high */
        delayUs(2);                         /* wait for signal to settle */
        row = (PTC->PDIR >> 10) & 0xF;      /* read all rows */
        PTE->PCOR = 0xF << 20;              /* set column data pins all low */
        if (row != 0) break;                /* if one of the input is low, some key is pressed. */
    }

    PTE->PDDR &= ~(0xF << 20);          /* disable all cols */
    if (col == 4)
        return 0;                       /* if we get here, no key is pressed */
 
    /* gets here when one of the rows has key pressed, check which column it is */
		/* col goes from 0 to 3 as shown in the col scan above */
   // if (row == 0x01) return col * 4 + 1;    /* key in column 0 */
   // if (row == 0x02) return col * 4 + 2;    /* key in column 1 */
   // if (row == 0x04) return col * 4 + 3;    /* key in column 2 */
   // if (row == 0x08) return col * 4 + 3;    /* key in column 3 */
		
		if (row == 0x01) return keymap[col + 0 * 4 + 1];    // key in column 0
    if (row == 0x02) return keymap[col + 1 * 4 + 1];    // key in column 1
    if (row == 0x04) return keymap[col + 2 * 4 + 1];    // key in column 2
    if (row == 0x08) return keymap[col + 3 * 4 + 1];    // key in column 3

    return 0;   /* just to be safe */
}

void set_timer(void) {
	// Variable to end loop
	int not_done = 1;
	unsigned char key;
	
	// Grab first digit of seconds
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("Enter secs (1s)");
	Set_Cursor(0,1);
	Print_LCD("  :  ");
	while (not_done) {
		key = keypad_getkey();
		if (is_num(key,9)){
			secs += (key - '0');
			not_done = 0;
		}
	}
	
	//Grab second digit of seconds
	not_done = 1;

	Set_Cursor(0,0);
	Print_LCD("Enter secs (10s)");
	Set_Cursor(1,0);
	Print_LCD(strcat("  :",(char*)secs));
	while (not_done) {
		key = keypad_getkey();
		if (is_num(key,5)) {
			secs += (key - '0')*10;
			not_done = 0;
		}
	}
	
	//Grab first minute digit
	not_done = 1;
	
	Set_Cursor(0,0);
	Print_LCD("Enter mins (1s)");
	Set_Cursor(0,1);
	Print_LCD(strcat("  : ",(char*)secs));
	while(not_done){
		key = keypad_getkey();
		if (is_num(key,9)){
			mins += (key - '0');
			not_done = 0;
		}
	}
	
	//Grab second minute digit
	not_done = 1;
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("Enter mins (10s)");
	Set_Cursor(0,1);
	Print_LCD(strcat((char*)mins,strcat(":",(char*)secs)));
	while(not_done){
		key = keypad_getkey();
		if (is_num(key,5)){
			mins += (key - '0')*10;
			not_done = 0;
		}
	}
}


void timer_countdown(void) {
	
	int not_done = 1;
	unsigned char key;
	while (not_done) {
		key = keypad_getkey();
		if (key == 'F'){
			pause_timer();
		}
		
		Clear_LCD();
		Set_Cursor(0,0);
		Print_LCD("Timer Active");
		Set_Cursor(0,1);
		Print_LCD(strcat((char*)mins,strcat(":",(char*)secs)));
		
		if (secs == 0) {
			mins -= 1;
			secs = 60;
		}
		else if (mins == 0 && secs == 0){
			not_done = 0;
		}
	}
}


void pause_timer(void) {
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("Paused D - quit");
	Set_Cursor(0,1);
	Print_LCD("E - Resume");
	
	int not_done = 1;
	unsigned char key;
	while (not_done){
		key = keypad_getkey();
		if (key == 'D'){
			mins = 0;
			secs = 1;
			not_done = 0;
		}
		else if (key == 'E') {
			not_done = 0;
		}
	}
	
}

void timer_complete(void) {
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("Timer Complete!");
	Set_Cursor(0,1);
	Print_LCD("C - Continue");
	
	int not_done = 1;
	unsigned char key;
	while (not_done) {
		key = keypad_getkey();
		if (key == 'C'){
			not_done = 0;
		}
	}
	
}


// This function can be passed a keypress, and will determine
// if the keypress is a valid number within range of count.
// This gets used to ensure that time input is 0-9 (for single-
// digit seconds and single digit minutes) and is 0-5 (for 10s
// seconds and 10s minutes)

bool is_num(unsigned char keypress, int count) {
	
	bool is_num = false;
	int x = keypress - '0';
	
	for (int i = 0; i <= count; i++){
		if (x == i)
			is_num = true;
	}
	
	return is_num;
	
}
/* delay n microseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
			
		//Run example code

		//LCD_Example();
	    unsigned char key;
    
    keypad_init();
    
		Init_LCD();				//Call initial setup function
		Clear_LCD();			//Ensure LCD is clear before beginning
	
		PTD->PDOR = 0xFFFFFFFF;

    set_timer();
}
