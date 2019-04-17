/*----------------------------------------------------------------------------
This project code demonstrates how to interface a ARM Cortex M0+ processor with
a LCD driver IC controller
*----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include "gpio_defs.h"
#include "LCD_4bit.h"

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
	
	Delay(5000000);
	
	Set_Cursor(0,1);
	Print_LCD("Number 6");

	
}
