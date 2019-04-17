/*----------------------------------------------------------------------------
This project code demonstrates how to interface a ARM Cortex M0+ processor with
a LCD driver IC controller
*----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "Lab7_Header.h"

void delayMs(int n);
void delayUs(int n);
void keypad_init(void);
char keypad_getkey(void);
void LED_init(void);
void LED_set(char value);

/* create a delay function */
void Delay(volatile unsigned int time_del) {
	while (time_del--) {
		;
	}
}

/*------------------------------------------------------------------------------
	Example for LCD interface
	*------------------------------------------------------------------------------*/
void LCD_Example(void) {
	
	Init_LCD();				//Call initial setup function
	Clear_LCD();			//Ensure LCD is clear before beginning
	
	//use a function call to initialize the LCD 
	// use a function call to Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("This is a test"); //Must have 16 letter space
	//Print_LCD(" Hello, World!:)"); //Must have 16 letter space
	Set_Cursor(0,1);
	Print_LCD("for Jacob :/"); //Must have 16 letter space
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
			
		//Run example code
		//LCD_Example();
	//Let's try making changes to display content
	Init_LCD();
	Clear_LCD();
	
	Set_Cursor(0,0);
	Print_LCD("This is test two");
	Set_Cursor(0,1);
	Print_LCD("Number 5");
	
	delayUs(5000);
	
	Set_Cursor(0,1);
	Print_LCD("Number 6");
	
	    unsigned char key;
    
    keypad_init();
    LED_init();

    while(1)
    {
        key = keypad_getkey();
		if(key == '1')			/* if key == '1' */
		{
				PTB->PDOR  = ~ MASK(RED_LED_POS);		/* turn on red LED*/

		}		
		if(key == '2')		    /* if key == '2' */
		{
				PTB->PDOR = 0xFFFFFFFF;				/* turn off red LED*/

		}		
		if(key == '4')            /* if key == 'E' */
		{
				PTB->PDOR  = ~ MASK(GREEN_LED_POS);				/* turn on green LED*/
		}	
		if(key == '5')            /* if key == 'D' */
		{
					PTB->PDOR = 0xFFFFFFFF;				/* turn off green LED*/
		}						   
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

/* initialize all three LEDs on the FRDM board */
void LED_init(void)
{
    SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
    SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
    PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO */
    PTB->PDDR |= 0x40000;       /* make PTB18 as output pin */
    PTB->PSOR |= 0x40000;       /* turn off red LED */
    PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO */
    PTB->PDDR |= 0x80000;       /* make PTB19 as output pin */
    PTB->PSOR |= 0x80000;       /* turn off green LED */
    PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
    PTD->PDDR |= 0x02;          /* make PTD1 as output pin */
    PTD->PSOR |= 0x02;          /* turn off blue LED */
}

/* turn on or off the LEDs according to bit 3-0 of the value */
void LED_set(char value)
{
    if (value == '1')     /* use bit 0 of value to control red LED */
        PTB->PCOR = 0x40000;    /* turn on red LED */
    else if (value == '2')
        PTB->PSOR = 0x40000;    /* turn off red LED */
          else if (value == 'E')
						PTB->PCOR = 0x80000;    /* turn on green LED */
					else if (value == 'D')
        PTB->PSOR = 0x80000;    /* turn off green LED */
}

/* delay n microseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */
void delayUs(int n)
{
    int i; int j;
    for(i = 0 ; i < n; i++) {
        for(j = 0; j < 5; j++) ;
    }
}

