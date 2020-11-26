#ifndef switches_included
#define switches_included

#include "msp430.h"

#define SW1 BIT0        //switch 1 is p2.0
#define SW2 BIT1        //switch 1 is p2.0
#define SW3 BIT2        //switch 1 is p2.0
#define SW4 BIT3        //switch 1 is p2.0

#define SWITCHES (SW1 | SW2 | SW3 | SW4) //4 switches on the board

unsigned int p2sw_read();
char switch_update_interrupt_sense();
void p2sw_init(unsigned char mask);
void switch_interrupt_handler();

extern char button_state;
#endif // included
