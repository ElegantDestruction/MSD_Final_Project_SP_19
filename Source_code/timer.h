#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

// I'm going to define each state as a function with a repeating
// loop. So when entering each state, the program should get 
// intentionally "stuck" until the conditions to exit the state
// are met.

void set_timer(void);
void timer_countdown(void);
void pause_timer(void);
void timer_complete(void);



#endif