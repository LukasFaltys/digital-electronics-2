#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake_game.h"

void print_field(struct snake_game *game) {
  struct snake_game_output output = snake_game_get_output(game);
  printf("Points: %d; ", output.points);
  switch (output.status) {
    case SNAKE_GAME_OUTPUT_STATUS_PLAYING:
      printf("Status: ⏩️;\n");
      break;
    case SNAKE_GAME_OUTPUT_STATUS_LOST:
      printf("Status: 💀;\n");
      break;
    case SNAKE_GAME_OUTPUT_STATUS_WON:
      printf("Status: 👑;\n");
      break;
  }

  for (int i = 0; i < SNAKE_GAME_HEIGHT; i++) {
    for (int j = 0; j < SNAKE_GAME_WIDTH; j++) {
      switch (output.field[i][j]) {
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_EMPTY:
          printf("⚪️");
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE:
          printf("❎");
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE_HEAD:
          printf("🐲");
          break;
        case SNAKE_GAME_OUTPUT_ITEM_TYPE_FOOD:
          printf("🪆");
          break;
      }
    }
    printf("\n");
  }
}

int main() {
  struct snake_game *game = snake_game_create();
  while (1) {
    print_field(game);
    switch (getchar()) {
      case 'w':
        snake_game_process_input(game, SNAKE_GAME_INPUT_UP);
        break;
      case 'a':
        snake_game_process_input(game, SNAKE_GAME_INPUT_LEFT);
        break;
      case 's':
        snake_game_process_input(game, SNAKE_GAME_INPUT_DOWN);
        break;
      case 'd':
        snake_game_process_input(game, SNAKE_GAME_INPUT_RIGHT);
        break;
      default:
        break;
    }
  }
}
