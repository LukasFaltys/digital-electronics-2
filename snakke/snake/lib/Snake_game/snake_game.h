#ifndef SNAKE_GAME_SNAKE_GAME_H
#define SNAKE_GAME_SNAKE_GAME_H

// Define the dimensions of the game board
#define SNAKE_GAME_WIDTH 64
#define SNAKE_GAME_HEIGHT 32

struct snake_game;

// Enum defining different inputs for the snake game
enum snake_game_input {
  SNAKE_GAME_INPUT_UP,
  SNAKE_GAME_INPUT_DOWN,
  SNAKE_GAME_INPUT_LEFT,
  SNAKE_GAME_INPUT_RIGHT
};

// Enum defining different types of items in the game field
enum snake_game_output_item_type {
  SNAKE_GAME_OUTPUT_ITEM_TYPE_EMPTY,
  SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE,
  SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE_HEAD,
  SNAKE_GAME_OUTPUT_ITEM_TYPE_FOOD
};

// Enum defining different game statuses
enum snake_game_output_status {
  SNAKE_GAME_OUTPUT_STATUS_PLAYING,
  SNAKE_GAME_OUTPUT_STATUS_LOST,
  SNAKE_GAME_OUTPUT_STATUS_WON
};

// Structure representing the output of the snake game
struct snake_game_output {
  int points;
  enum snake_game_output_status status;
  enum snake_game_output_item_type field[SNAKE_GAME_HEIGHT][SNAKE_GAME_WIDTH];
};

// Creates a new instance of the snake game
struct snake_game *snake_game_create();

// Destroys the snake game instance and frees memory
void snake_game_destroy(struct snake_game *game);

// Processes user input to update the game state
void snake_game_process_input(struct snake_game *game, enum snake_game_input input);

// Retrieves the output/status of the snake game
struct snake_game_output snake_game_get_output(struct snake_game *game);

#endif //SNAKE_GAME_SNAKE_GAME_H
