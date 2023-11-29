#include <avr/io.h>         
#include <avr/interrupt.h>  
#include <stdlib.h>
#include "gpio.h"
#include "oled.h"
#include "timer.h"  
#include "snake_game.h"      

#define BTN_UP 3
#define BTN_DOWN 4
#define BTN_RIGHT 5
#define BTN_LEFT 2

struct snake_game game;
snake_game_input input = SNAKE_GAME_INPUT_RIGHT;
uint8_t apple[8][8] = {
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 1, 0}
  };
uint8_t scull[8][16] = {
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1}
};
uint8_t crown[8][16] = {
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int main(void)
{
  GPIO_mode_input_pullup(&DDRD,BTN_UP);
  GPIO_mode_input_pullup(&DDRD,BTN_DOWN);
  GPIO_mode_input_pullup(&DDRD,BTN_RIGHT);
  GPIO_mode_input_pullup(&DDRD,BTN_LEFT);

  oled_init(OLED_DISP_ON);
  oled_clrscr();

  snake_game_create(&game);

  TIM1_overflow_1s();
  TIM1_overflow_interrupt_enable();
  sei();

  while (1);      
  return 0;
}

void process_input()
{
  if (GPIO_read(&PIND,BTN_LEFT) == 0){
    input = SNAKE_GAME_INPUT_LEFT;
  }else if (GPIO_read(&PIND,BTN_RIGHT) == 0){
    input = SNAKE_GAME_INPUT_RIGHT;
  }else if (GPIO_read(&PIND,BTN_DOWN) == 0){
    input = SNAKE_GAME_INPUT_DOWN;
  }else if (GPIO_read(&PIND,BTN_UP) == 0) {
    input = SNAKE_GAME_INPUT_UP;
  }
  snake_game_process_input(&game,input);
}

void draw_output()
{
  oled_clrscr();
  for (int i = 0; i < game.snake_length; i++ ){
    for (int j = 0; j < 8; j++){
      for (int k = 0; k < 8; k++){
        oled_drawPixel(game.snake_positions[i].y * 8 + j,game.snake_positions[i].x * 8 + k,WHITE);
      }
    }
  }
  
  for (int i = 0; i < 8; i++ ){
    for (int j = 0; j < 8; j++){
      if (apple[i][j]==1){
        oled_drawPixel(game.food_position.y * 8 + j,game.food_position.x * 8 + i,WHITE);
      }
    }
  }
 
  oled_display();
}

ISR(TIMER1_OVF_vect)
{
  if (game.status==SNAKE_GAME_OUTPUT_STATUS_LOST){
    oled_clrscr();
    for (int i = 0; i < 8; i++ ){
      for (int j = 0; j < 16; j++){
      if (scull[i][j]==0){
        for (int g = 0; g < 8; g++ ){
          for (int h = 0; h < 8; h++){
            oled_drawPixel(j*8+h,i*8+g,WHITE);
          }
        }
      }
    }
  }
  } else if (game.status==SNAKE_GAME_OUTPUT_STATUS_WON){
    oled_clrscr();
    for (int i = 0; i < 8; i++ ){
      for (int j = 0; j < 16; j++){
      if (crown[i][j]==0){
        for (int g = 0; g < 8; g++ ){
          for (int h = 0; h < 8; h++){
            oled_drawPixel(j*8+h,i*8+g,WHITE);
          }
        }
      }
    }
  }
  } else{
  draw_output();
  process_input();
  }
  oled_display();
}
