/*#include <oled.h>

int main(void)
{
    oled_init(OLED_DISP_ON);
    oled_clrscr();





 
 GRAPHICMODE;
oled_drawPixel(3,1,WHITE);
oled_drawPixel(5,1,WHITE);





    // Copy buffer to display RAM
    oled_display();

    while (1) {
        ;
    }

    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake_game.h"
#include <gpio.h> 
#include "timer.h" 
#include <oled.h>

#define UP PB1  
#define DOWN PB2
#define LEFT PB3
#define RIGHT PB4

uint8_t direction = 1;

void print_field(struct snake_game *game) {
oled_init(OLED_DISP_ON);
oled_clrscr();
  struct snake_game_output output = snake_game_get_output(game);

  switch (output.status) {
  
      break;
    case SNAKE_GAME_OUTPUT_STATUS_LOST:
      
      break;
    case SNAKE_GAME_OUTPUT_STATUS_WON:
      
      break;
  }

  for (int i = 0; i < SNAKE_GAME_HEIGHT; i++) {
    for (int j = 0; j < SNAKE_GAME_WIDTH; j++) {
      switch (output.field[i][j]) {
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_EMPTY:
          
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE:
          GRAPHICMODE;
          oled_drawPixel(i,j,WHITE);
          oled_display();
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE_HEAD:
          GRAPHICMODE;
          oled_drawPixel(i,j,WHITE);
          oled_display();
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_FOOD:
          GRAPHICMODE;
          oled_drawPixel(i,j,WHITE);
          oled_display();
          break;
      }
    }
   
  }
  oled_clrscr();
}

int main(void)
{
struct snake_game *game= snake_game_create ();

GPIO_mode_input_pullup(&DDRB, UP);
GPIO_mode_input_pullup(&DDRB, DOWN);
GPIO_mode_input_pullup(&DDRB, LEFT);
GPIO_mode_input_pullup(&DDRB, RIGHT);





while (1)
    {
         print_field(game);
        if (GPIO_read(&DDRB,UP)==1){
            direction =1;
        }
        else if (GPIO_read(&DDRB,DOWN)==1){
            direction =2;
        }
        else if (GPIO_read(&DDRB,LEFT)==1){
            direction =3;
        }
        else if (GPIO_read(&DDRB,RIGHT)==1){
            direction =4;
        }
    
    switch (direction) {
      case 1:
        snake_game_process_input(game, SNAKE_GAME_INPUT_UP);
       
        break;
      case 2:
        snake_game_process_input(game, SNAKE_GAME_INPUT_LEFT);
        
        break;
      case 3:
        snake_game_process_input(game, SNAKE_GAME_INPUT_DOWN);
        
        break;
      case 4:
        snake_game_process_input(game, SNAKE_GAME_INPUT_RIGHT);
      
        break;
      default:
        break;
    }
    }

    return 0;

   
}











