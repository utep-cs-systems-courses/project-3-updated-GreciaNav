#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

short changeMade = 1;

void wdt_c_handler()
{
  static char interrupt_count = 0;
  
  if (++interrupt_count == 62 && button_state == 0) { //Called per 1/4th of a sec, dancing sonic
    changeMade = 1;
    interrupt_count = 0;
  }
  else if (interrupt_count == 250 && button_state == 1) { //Displays Zelda scene
    changeMade = 1;
    interrupt_count = 0; 
  }    
  else if (interrupt_count == 250 && button_state == 2) { //Draws diamond, changes color per sec
    changeMade = 1;
    interrupt_count = 0;
  }
  else if ((interrupt_count == 3) && button_state == 3) { //Different red intensities
    changeMade = 1;
    interrupt_count = 0;
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();
  p2sw_init(SWITCHES);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_WHITE);
  while (1) {			/* forever */
    if (changeMade) { 
      changeMade = 0;
      switch (button_state) {
      case 0: //Dancing Sonic
	turn_red_off();
	buzz_song_advance();
	break;
      case 1: //Displays Zelda scene
	turn_red_off();
	buzzer_set_period(0);
	clearScreen(COLOR_BLACK);
	drawZeldaScene();
	break;
      case 2: //Color changing diamond
	turn_red_off();
	buzzer_set_period(0);
	draw_diamonds();
	break;
      case 3: //Dim light
	buzzer_set_period(0);
	dim();
      }	
    }  
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
