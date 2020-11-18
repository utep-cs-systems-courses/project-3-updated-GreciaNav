/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_WHITE);

  drawString5x7(20,20, "go fast", COLOR_RED, COLOR_WHITE);
  drawLink(70,40,COLOR_WHITE);
  drawSonic(80,80, COLOR_WHITE);
  drawSonic2(20,50, COLOR_WHITE);
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
