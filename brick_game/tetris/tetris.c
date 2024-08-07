#include "tetris.h"

GameInfo_t *init_game() {
  // init field for game //
  GameInfo_t *game = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  game->field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    game->field[i] = (int *)calloc(WIDTH, sizeof(int));
  }

  // init next figure field //
  game->next = (int **)calloc(BLOCK_SIZE, sizeof(int *));
  for (int i = 0; i < BLOCK_SIZE; i++) {
    game->next[i] = (int *)calloc(BLOCK_SIZE, sizeof(int));
  }

  // init default stat //
  game->score = 0;
  game->level = 0;
  game->speed = 1;
  game->pause = 0;
  game->status = Start;

  // init record //
  game->high_score = 0;  // get record from db //

  // func for getting random figure //
};