#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#include <stdbool.h>

// I'm going to define each state as a function with a repeating
// loop. So when entering each state, the program should get 
// intentionally "stuck" until the conditions to exit the state
// are met.

int hours = 0;
int mins = 0;
int secs = 0;
bool restarted;

void mode_select(void);
void stopwatch(void);
void set_timer(void);
void timer_countdown(void);
void pause_timer(void);
void timer_complete(void);
bool is_num(unsigned char, int);
void lcd_printInt(unsigned int number);
void lcd_print00(unsigned char number);
void getDecStr ( uint32_t val, uint8_t* str, uint8_t len);
void LED_init(void);

#endif
