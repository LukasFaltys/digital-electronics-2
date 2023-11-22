#include <stdio.h>
#include <stdlib.h>
#include "snake_game.h"
#include <gpio.h> 
#include "timer.h" 
#include <oled.h>


int main (void) {

 /* GRAPHICMODE;
   oled_drawPixel(64,32,WHITE);
          oled_display();*/
struct snake_game *game= snake_game_create ();
oled_init(OLED_DISP_ON);
oled_clrscr();
  struct snake_game_output output = snake_game_get_output(game);
  
 /* for (int i = 0; i < SNAKE_GAME_HEIGHT; i++) {
    for (int j = 0; j < SNAKE_GAME_WIDTH; j++) {*/
  
      switch (output.field[64][32]) {
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_EMPTY:
          
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE:
          GRAPHICMODE;

          oled_drawPixel(64,32,WHITE);
          oled_display();
          
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE_HEAD:
          GRAPHICMODE;
          oled_drawPixel(64,32,WHITE);
          oled_display();
          break;
        /*case SNAKE_GAME_OUTPUT_ITEM_TYPE_FOOD:
          
          oled_drawPixel(i,j,WHITE);
          oled_display();
          
          break;*/
          
      //}
    //}
   
  }

  return 1;
}