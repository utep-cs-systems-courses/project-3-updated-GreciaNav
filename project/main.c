#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

short changeMade = 1;
u_int fontFgColor = COLOR_BLACK;

void wdt_c_handler()
{
  static char interrupt_count = 0;
  
  if (++interrupt_count == 62 && button_state == 0) { //Called per 1/4th of a sec, plays song
    turn_red_off();
    buzz_song_advance();
    interrupt_count = 0;
    changeMade = 1;
  }
  else if (interrupt_count == 250 && button_state == 1) { //Siren buzz
    turn_red_off();
    buzzer_set_period(0);
    clearScreen(COLOR_BLACK);
    drawZeldaScene();
    changeMade = 1;
  }    
  else if (interrupt_count == 62 && button_state == 2) { //Advances siren state, switches leds
    turn_red_off();
    buzz_song_advance();
    interrupt_count = 0;
    changeMade = 1;
  }
  else if ((interrupt_count == 3) && button_state == 3) { //Different red intensities, buzzer off
    buzzer_set_period(0);
    dim();
    interrupt_count = 0;
    changeMade = 1;
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
    static char color = 0;
    if (changeMade) 
      changeMade = 0;
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



