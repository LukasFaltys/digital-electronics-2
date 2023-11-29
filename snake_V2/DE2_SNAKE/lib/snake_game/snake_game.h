#ifndef SNAKE_GAME_SNAKE_GAME_H
#define SNAKE_GAME_SNAKE_GAME_H
#include <stdint.h>
// Define the dimensions of the game board
#define SNAKE_GAME_WIDTH 16
#define SNAKE_GAME_HEIGHT 8

// Enum defining different inputs for the snake game
typedef uint8_t snake_game_input;
#define SNAKE_GAME_INPUT_UP 0
#define SNAKE_GAME_INPUT_DOWN 1
#define SNAKE_GAME_INPUT_LEFT 2
#define SNAKE_GAME_INPUT_RIGHT 3

// Enum defining different types of items in the game field
typedef uint8_t snake_game_output_item_type;
#define SNAKE_GAME_OUTPUT_ITEM_TYPE_EMPTY 0
#define SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE 1
#define SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE_HEAD 2
#define SNAKE_GAME_OUTPUT_ITEM_TYPE_FOOD 3


// Enum defining different game statuses
typedef uint8_t snake_game_output_status;
#define SNAKE_GAME_OUTPUT_STATUS_PLAYING 0
#define SNAKE_GAME_OUTPUT_STATUS_LOST 1
#define SNAKE_GAME_OUTPUT_STATUS_WON 2

// Structure to hold x and y coordinates for positions in the game
struct snake_game_position {
  uint8_t x, y;
};

// Structure to represent the entire snake game
struct snake_game {
  snake_game_output_status status;
  uint32_t snake_length;
  struct snake_game_position snake_positions[SNAKE_GAME_WIDTH * SNAKE_GAME_HEIGHT];
  struct snake_game_position food_position;
};

// Creates a new instance of the snake game
void snake_game_create(struct snake_game *game);

// Processes user input to update the game state
void snake_game_process_input(struct snake_game *game, snake_game_input input);

#endif //SNAKE_GAME_SNAKE_GAME_H

