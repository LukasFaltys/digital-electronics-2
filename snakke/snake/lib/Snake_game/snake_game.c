#include <stdlib.h>
#include <time.h>
#include "snake_game.h"

// Structure to hold x and y coordinates for positions in the game
struct snake_game_position {
  int x, y;
};

// Doubly linked list structure to represent the snake's body
struct snake_game_list {
  struct snake_game_position position;
  struct snake_game_list *prev;
  struct snake_game_list *next;
};

// Structure to represent the entire snake game
struct snake_game {
  struct snake_game_list *head;
  struct snake_game_list *tail;
  struct snake_game_output output;
  struct snake_game_position food_position;
};

// Creates a new node for the snake's body
static struct snake_game_list *snake_game_list_create(struct snake_game_position position) {
  struct snake_game_list *new = malloc(sizeof(struct snake_game_list));
  if (new == NULL) {
    return NULL;
  }

  new->position = position;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

// Adds a new node to the beginning of the snake's body
static struct snake_game_list *
snake_game_list_prepend(struct snake_game_list *head, struct snake_game_position position) {
  struct snake_game_list *new = snake_game_list_create(position);
  if (head == NULL) {
    return new;
  }

  new->next = head;
  head->prev = new;
  return new;
}

// Removes the tail node from the snake's body
static struct snake_game_list *snake_game_list_pop_tail(struct snake_game_list *tail) {
  if (tail == NULL) {
    return NULL;
  }

  struct snake_game_list *new_tail = tail->prev;
  free(tail);
  if (new_tail == NULL) {
    return NULL;
  }

  new_tail->next = NULL;
  return new_tail;
}

// Frees memory allocated for the snake's body nodes
static void snake_game_list_free(struct snake_game_list *head) {
  struct snake_game_list *curr = head;
  struct snake_game_list *temp;
  while (curr != NULL) {
    temp = curr;
    curr = head->next;
    free(temp);
  }
}

// Generates a random integer within a specified range
static int random_int_in_range(int min, int max) {
  srand(time(NULL));
  return min + rand() % (max - min);
}

// Places food at a random position on the game board
static void place_food(struct snake_game *game) {
  game->food_position = (struct snake_game_position) {
    .x = random_int_in_range(0, SNAKE_GAME_HEIGHT),
    .y = random_int_in_range(0, SNAKE_GAME_WIDTH)
  };
}

// Updates the output field representing the game state
static void update_output_field(struct snake_game *game) {
  // Reset the field to empty
  for (int i = 0; i < SNAKE_GAME_HEIGHT; i++) {
    for (int j = 0; j < SNAKE_GAME_WIDTH; j++) {
      game->output.field[i][j] = SNAKE_GAME_OUTPUT_ITEM_TYPE_EMPTY;
    }
  }

  // Update snake's head and body positions on the field
  struct snake_game_list *head = game->head;
  game->output.field[head->position.x][head->position.y] = SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE_HEAD;

  for (struct snake_game_list *node = head->next; node != NULL; node = node->next) {
    game->output.field[node->position.x][node->position.y] = SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE;
  }

  // Place food on the field
  game->output.field[game->food_position.x][game->food_position.y] = SNAKE_GAME_OUTPUT_ITEM_TYPE_FOOD;
}

// Creates a new snake game instance
struct snake_game *snake_game_create() {
  struct snake_game *game = malloc(sizeof(struct snake_game));
  if (game == NULL) {
    return NULL;
  }

  struct snake_game_list *initial_node = snake_game_list_create(
    (struct snake_game_position) {
      .x = SNAKE_GAME_HEIGHT / 2,
      .y = SNAKE_GAME_WIDTH / 2
    });
  game->head = initial_node;
  game->tail = initial_node;
  game->output.points = 1;

  place_food(game);
  update_output_field(game);

  return game;
}

// Destroys the snake game instance and frees memory
void snake_game_destroy(struct snake_game *game) {
  snake_game_list_free(game->head);
  free(game);
}

// Processes user input to move the snake and update the game state
void snake_game_process_input(struct snake_game *game, enum snake_game_input input) {
  if (game->output.status != SNAKE_GAME_OUTPUT_STATUS_PLAYING) {
    return;
  }

  struct snake_game_position new_position;
  switch (input) {
    case SNAKE_GAME_INPUT_UP:
      new_position.x = game->head->position.x - 1;
      new_position.y = game->head->position.y;
      break;
    case SNAKE_GAME_INPUT_DOWN:
      new_position.x = game->head->position.x + 1;
      new_position.y = game->head->position.y;
      break;
    case SNAKE_GAME_INPUT_LEFT:
      new_position.x = game->head->position.x;
      new_position.y = game->head->position.y - 1;
      break;
    case SNAKE_GAME_INPUT_RIGHT:
      new_position.x = game->head->position.x;
      new_position.y = game->head->position.y + 1;
      break;
  }

  // Check if the new position is within the game boundaries
  if (new_position.x < 0 || new_position.x >= SNAKE_GAME_HEIGHT || new_position.y < 0 ||
      new_position.y >= SNAKE_GAME_WIDTH) {
    game->output.status = SNAKE_GAME_OUTPUT_STATUS_LOST;
    return;
  }

  // Process different scenarios based on the type of field the snake is moving to
  switch (game->output.field[new_position.x][new_position.y]) {
    case SNAKE_GAME_OUTPUT_ITEM_TYPE_EMPTY:
      game->head = snake_game_list_prepend(game->head, new_position);
      game->tail = snake_game_list_pop_tail(game->tail);
      break;
    case SNAKE_GAME_OUTPUT_ITEM_TYPE_FOOD:
      game->output.points += 1;
      game->output.status = game->output.points == SNAKE_GAME_HEIGHT * SNAKE_GAME_WIDTH
                            ? SNAKE_GAME_OUTPUT_STATUS_WON
                            : SNAKE_GAME_OUTPUT_STATUS_PLAYING;
      game->head = snake_game_list_prepend(game->head, new_position);
      place_food(game);
      break;
    case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE_HEAD:
    case SNAKE_GAME_OUTPUT_ITEM_TYPE_SNAKE:
      game->output.status = SNAKE_GAME_OUTPUT_STATUS_LOST;
      return;
  }

  // Update the game field after the changes
  update_output_field(game);
}

// Retrieves the output
struct snake_game_output snake_game_get_output(struct snake_game *game) {
  return game->output;
}