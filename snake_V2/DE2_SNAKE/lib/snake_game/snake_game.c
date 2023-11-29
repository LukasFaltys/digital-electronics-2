#include <stdlib.h>
#include "snake_game.h"
#include <time.h> 

// Adds a new node to the beginning of the snake's body
void snake_game_positions_prepend(struct snake_game *game, struct snake_game_position position) {
  struct snake_game_position prev = position;
  game->snake_length++;
  for (int i = 0; i < game->snake_length; i++) {
    struct snake_game_position temp = prev;
    prev = game->snake_positions[i];
    game->snake_positions[i] = temp;
  }
}

// Places food at a random position on the game board
static void snake_game_place_food(struct snake_game *game) {
  game->food_position = (struct snake_game_position) {
    .x = ((uint8_t)game->snake_length * 3313 * game->snake_positions[(uint8_t)game->snake_length-1].y) % SNAKE_GAME_HEIGHT,
    .y = ((uint8_t)game->snake_length * 7541 * game->snake_positions[(uint8_t)game->snake_length-1].x) % SNAKE_GAME_WIDTH
  };
}

// Creates a new instance of the snake game
void snake_game_create(struct snake_game *game) {
  game->status = SNAKE_GAME_OUTPUT_STATUS_PLAYING;
  game->snake_length = 1;
  game->snake_positions[0] = (struct snake_game_position) {
    .x = SNAKE_GAME_HEIGHT / 2, .y = SNAKE_GAME_WIDTH / 2
  };
  snake_game_place_food(game);
}

// Processes user input to move the snake and update the game state
void snake_game_process_input(struct snake_game *game, snake_game_input input) {
  if (game->status != SNAKE_GAME_OUTPUT_STATUS_PLAYING) {
    return;
  }

  struct snake_game_position new_position;
  switch (input) {
    case SNAKE_GAME_INPUT_UP:
      new_position.x = game->snake_positions[0].x - 1;
      new_position.y = game->snake_positions[0].y;
      break;
    case SNAKE_GAME_INPUT_DOWN:
      new_position.x = game->snake_positions[0].x + 1;
      new_position.y = game->snake_positions[0].y;
      break;
    case SNAKE_GAME_INPUT_LEFT:
      new_position.x = game->snake_positions[0].x;
      new_position.y = game->snake_positions[0].y - 1;
      break;
    case SNAKE_GAME_INPUT_RIGHT:
      new_position.x = game->snake_positions[0].x;
      new_position.y = game->snake_positions[0].y + 1;
      break;
    default:
      return;
  }

  // Check if the new position is within the game boundaries
  if (new_position.x < 0 || new_position.x >= SNAKE_GAME_HEIGHT || new_position.y < 0 ||
      new_position.y >= SNAKE_GAME_WIDTH) {
    game->status = SNAKE_GAME_OUTPUT_STATUS_LOST;
    return;
  }

  // Check if the new position is occupied by the snake
  for (int i = 0; i < game->snake_length; i++) {
    if (game->snake_positions[i].x == new_position.x && game->snake_positions[i].y == new_position.y) {
      game->status = SNAKE_GAME_OUTPUT_STATUS_LOST;
      return;
    }
  }

  // Check if the new position is occupied by the food
  if (new_position.x == game->food_position.x && new_position.y == game->food_position.y) {
    snake_game_positions_prepend(game, new_position);
    snake_game_place_food(game);
    return;
  }

  snake_game_positions_prepend(game, new_position);
  game->snake_length--;
}
