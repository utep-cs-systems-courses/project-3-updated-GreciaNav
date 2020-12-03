#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "notes.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"

char toggle_state = 0; //Determines current toggle state for dimming
char dim_state = 0; //Determines state of dim()
char repeated = 0; //Used to control how many times funcitons are called in dim
char diamond_color_state = 0;

void draw_diamonds() //Draws diamond that alternates colors
{
  switch (diamond_color_state) {
  case 0:
    clearScreen(COLOR_BLACK);
  case 1:
    drawDiamond(60,COLOR_CYAN);
    diamond_color_state++;
    break;
  case 2:
    drawDiamond(60,COLOR_BLUE);
    diamond_color_state++;
    break;
  case 3:
    drawDiamond(60,COLOR_PURPLE);
    diamond_color_state = 0;
    break;
  }   
}

void draw_zelda_scene()
{
  static char colorState = 0;
  u_int textColor; 
  switch (colorState) {
  case 0:
    clearScreen(COLOR_BLACK);
  case 1:
    textColor = COLOR_WHITE;
    colorState++;
    break;
  case 2:
    textColor = COLOR_RED;
    colorState = 0;
    break;
  }   
  
  drawString11x16(0,5,"It's 2020.", textColor, COLOR_BLACK);
  drawString11x16(0,22,"You've met", textColor, COLOR_BLACK);
  drawString11x16(0,39,"a terrible", textColor, COLOR_BLACK);
  drawString11x16(0,56,"fate...", textColor, COLOR_BLACK);
  drawString11x16(0,73,"Haven't", textColor, COLOR_BLACK);
  drawString11x16(0,90,"you?", textColor, COLOR_BLACK);
  drawLink(50,107, COLOR_BLACK);
}
  
void turn_red_off() //Turns red off
{
  red_on = 0;
  led_update();
}

void toggle_red() //Red at 50% intensity		
{
  if (repeated < 2) {
    repeated++;  
    toggle_state = toggle_red_state_machine(toggle_state);
    led_update();
  }
  else {
    repeated = 0;
    dim_state = 1;
  }   
}

void toggle_red75() //Red at 75% intensity
{
  if (repeated < 3) {
    repeated++;
    switch (toggle_state) {
    case 0: //Red on
      red_on = 1;
      toggle_state = 1;
      break;
    case 1: //Red on 
      red_on = 1;
      toggle_state = 2;
      break;
    case 2: //Red off
      red_on = 0;
      toggle_state = 0;
      break;
    }
    led_update();
  }
  else {
    repeated = 0;
    dim_state = 2;
  }   
}  

void toggle_red25() //Red at 25% intensity
{
  if (repeated < 3) {
    repeated++;
    switch (toggle_state) {
    case 0: //Red off
      red_on = 0;
      toggle_state = 1;
      break;
    case 1: //Red off
      red_on = 0;
      toggle_state = 2;
      break;
    case 2: //Red on
      red_on = 1;
      toggle_state = 0;
      break;
    }
    led_update();
  }
  else {
    repeated = 0;
    dim_state = 0;
  }  
}

void turn_green_on() //Only green will be on
{
  green_on = 1;
  red_on = 0;
  led_update();
}

void turn_red_on() //Only red will be on
{
  red_on = 1;
  green_on = 0;
  led_update();
}

void buzz_song_advance() //Plays Sonic song
{
  static char curr_note = 0;
  
  //Alternating Sonic sprites
  if ((curr_note % 2) == 0) 
    drawSonic(50,50,COLOR_BLACK, COLOR_BLUE); 
  else 
    drawSonic2(50,50,COLOR_BLACK, COLOR_BLUE);
     
  switch(curr_note) {
  case 0:
    clearScreen(COLOR_BLACK);
  case 1: //Plays note G
    buzzer_set_period(G);
    curr_note++;
    break;
  case 2: //Plays note E, hold 2 beats
    buzzer_set_period(E);
    curr_note++;
    break;
  case 4: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 5: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 6: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 7: //Plays note F, hold 2 beats
    buzzer_set_period(F);
    curr_note++;
    break;
  case 9: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 10: //Plays note D, hold 2 beats
    buzzer_set_period(D);
    curr_note++;
    break;
  case 12: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 13: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 14: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 15: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 16: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 17: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 18: //Break in notes
    buzzer_set_period(0);
    curr_note++;
  case 19: //Plays note C, hold 2 beats
    buzzer_set_period(Cn);
    curr_note++;
    break;
  case 21: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 22: //Plays note A#, hold 2 beats
    buzzer_set_period(ASH);
    curr_note++;
    break;
  case 24: //Plays note D, hold 2 beats
    buzzer_set_period(D);
    curr_note++;
    break;
  case 26: //Song end, back to beggining
    buzzer_set_period(0);
    curr_note = 0;
    break;
  default:
    curr_note++;
  }   
}
