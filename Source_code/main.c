/*----------------------------------------------------------------------------
This project code demonstrates how to interface a ARM Cortex M0+ processor with
a LCD driver IC controller
*----------------------------------------------------------------------------*/

/*
#include <MKL25Z4.H>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "delay.h"
#include "timer.h"

void delayMs(int n);
void delayUs(int n);
void keypad_init(void);
char keypad_getkey(void);


// create a delay function */
/*
void Delay(volatile unsigned int time_del) {
	while (time_del--) {
		;
	}
}

//----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
 /*
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


//----------------------------------------------------------------------------
  Keypad Code
 *----------------------------------------------------------------------------*/


/* this function initializes PortC that is connected to the keypad.
 * All pins are configured as GPIO input pin with pull-up enabled.
 */
/*
void keypad_init(void)
{
    SIM->SCGC5 |= 0x0800;      enable clock to Port C */
  //  SIM->SCGC5 |= 0x2000;       /* enable clock to Port E */
    
    //PORTC->PCR[10] = 0x100;     /* make PTC10 pin as GPIO */
   //PORTC->PCR[11] = 0x100;     /* make PTC11 pin as GPIO */
    //PORTC->PCR[12] = 0x100;     /* make PTC12 pin as GPIO */
    //PORTC->PCR[13] = 0x100;     /* make PTC13 pin as GPIO */
    
    //PORTE->PCR[20] = 0x100;     /* make PTE20 pin as GPIO */
    //PORTE->PCR[21] = 0x100;     /* make PTE21 pin as GPIO */
    //PORTE->PCR[22] = 0x100;     /* make PTE22 pin as GPIO */
    //PORTE->PCR[23] = 0x100;     /* make PTE23 pin as GPIO */
    
  //  PTC->PDDR &= ~(0xF << 10);  /* make PTC13-10 as inputs connected to rows */
  //  PTE->PDDR &= ~(0xF << 20);  /* make PTE23-20 as inputs connected to columns */
//}

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




