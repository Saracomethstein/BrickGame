#include "tetris.h"

GameInfo_t *init_game() {
  // init field for game //
  GameInfo_t *gameInfo = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  gameInfo->field = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    gameInfo->field[i] = (int *)calloc(WIDTH, sizeof(int));
  }

  // init next figure field //
  gameInfo->next = (int **)calloc(BLOCK_SIZE, sizeof(int *));
  for (int i = 0; i < BLOCK_SIZE; i++) {
    gameInfo->next[i] = (int *)calloc(BLOCK_SIZE, sizeof(int));
  }

  // init default stat //
  gameInfo->score = 0;
  gameInfo->level = 0;
  gameInfo->speed = 1;
  gameInfo->pause = 0;
  gameInfo->status = Start;

  // init record //
  gameInfo->high_score = 0;  // get record from db //

  // func for getting random figure //
  choice_tetramino(gameInfo)
};

void choice_tetromino(GameInfo_t *gameInfo) {
  int next_id = rand() % 7;
  int block_id = rand() % 7;
  int flag = 0;

  // check next tetramino, if free -> flag = 0 //
  for (i = 0; i < BLOCK_SIZE; i++) {
    for (j = 0; j < BLOCK_SIZE; j++) {
      if (gameInfo->next[i][j] != 0) {
        flag = 1;
        break;
      }
    }
  }

  if (flag == 0) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        gameInfo->block[i][j] = tetrominos[block_id][i][j];
      }
    }
  } else {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      for (int j = 0; j < BLOCK_SIZE; j++) {
        gameInfo->block[i][j] = gameInfo->next[i][j];
      }
    }
  }

  // get next tetromino //
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      gameInfo->next[i][j] = tetrominos[next_id][i][j];
    }
  }
}