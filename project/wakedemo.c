#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static char blink_buz_count = 0;
  /*
  if (++blink_buz_count == 62 && button_state == 0) { //Called per 1/4th of a sec, plays song
    buzz_song_advance();
    blink_buz_count = 0;
  }
  else if ((blink_buz_count % 25) == 0 && button_state == 1) //Siren buzz
     buzzer_advance();
  else if ((blink_buz_count == 62) && button_state == 1) { //Advances siren state, switches leds
    siren_state_advance();
    blink_buz_count = 0;
  }
  else if (button_state == 2) { //Only green led on, buzzer off
    buzzer_set_period(0);
    turn_green_on();
  }
  else if ((blink_buz_count == 3) && button_state == 3) { //Different red intensities, buzzer off
    buzzer_set_period(0);
    dim();
    blink_buz_count = 0;
    }*/
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  //led_init();
  //buzzer_init();
  p2sw_init(SWITCHES);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_WHITE);
  while (1) {			/* forever */
    static char color = 0;/*
    if (redrawScreen) {
      redrawScreen = 0;
      switch (color) {
      case 0:
	drawSonic(50,50,COLOR_WHITE);
	color++;
	break;
      case 1:
	drawSonic2(50,50, COLOR_WHITE);
	color = 0;
	break;
	}*/
    if (button_state == 0)
      drawSonic(50,50, COLOR_WHITE);
    else if (button_state == 1)
      drawString5x7(20,20, "world", fontFgColor, COLOR_BLUE);
    else if (button_state == 2)
      drawString5x7(20,20, "go", fontFgColor, COLOR_BLUE);
    else if (button_state == 3)
      drawString5x7(20,20, "fast", fontFgColor, COLOR_BLUE);
    //}
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



