#include <MKL25Z4.H>
#include <stdint.h>
#include <string.h>
#include "timer.h"
#include "LCD_4bit.h"


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
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("Enter secs (10s)");
	Set_Cursor(0,1);
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
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("Enter mins (1s)");
	Set_Cursor(0,1);
	Print_LCD(strcat("  :",(char*)secs));
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
