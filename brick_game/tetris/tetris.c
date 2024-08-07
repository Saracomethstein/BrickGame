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

// put a block on the field //
void put_block(GameInfo_t *gameInfo) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (gameInfo->block[i][j] == 1) {
        gameInfo->field[gameInfo->block_row + i][gameInfo->block_col + j] = 1;
      }
    }
  }
}

// clear block on the field //
void clear_block(GameInfo_t *gameInfo) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (gameInfo->block[i][j] == 1) {
        gameInfo->field[gameInfo->block_row + i][gameInfo->block_col + j] = 0;
      }
    }
  }
}

void move_down(GameInfo_t *gameInfo) {
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (gameInfo->block[i][j] == 1) {
        int new_row = gameInfo->block_row + i + 1;
        int new_col = gameInfo->block_col + j;

        if (new_row > HEIGHT - 1 || gameInfo->field[new_row][new_col] == 2) {
          gameInfo->status = Sig;
          return;
        }
      }
    }
  }

  clear_block(gameInfo);
  put_block(gameInfo);
  gameInfo->block_row++;
}

void move_left(GameInfo_t *gameInfo) {
  for (int i = 0; i < HEIGHT; i++) {
    if (gameInfo->field[i][0] == 1) {
      return;
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (gameInfo->block[i][j] == 1) {
        if (gameInfo->field[gameInfo->block_row + i]
                           [gameInfo->block_col + j - 1] == 2) {
          return;
        }
      }
    }
  }

  clear_block(gameInfo);
  put_block(gameInfo);
  gameInfo->block_col--;
}

void move_right(GameInfo_t *gameInfo) {
  for (int i = 0; i < HEIGHT; i++) {
    if (gameInfo->field[i][WIDTH - 1] == 1) {
      return;
    }
  }

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (gameInfo->block[i][j] == 1) {
        if (gameInfo->field[gameInfo->block_row + i]
                           [gameInfo->block_col + j + 1] == 2) {
          return;
        }
      }
    }
  }

  clear_block(gameInfo);
  put_block(gameInfo);
  gameInfo->block_col++;
}

// rotation termino //
void rotate_termino(GameInfo_t *gameInfo) {
  int tmp[BLOCK_SIZE][BLOCK_SIZE];

  // copy termino //
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      tmp[i][j] = gameInfo->block[i][j];
    }
  }

  if (allow_rotate(gameInfo, tmp) == 0 && check_square(gameInfo)) {
    clear_block(gameInfo);

    for (int i = 0; i < BLOCK_SIZE; ++i) {
      for (int j = 0; j < BLOCK_SIZE; ++j) {
        gameInfo->block[i][j] = tmp[BLOCK_SIZE - j - 1][i];
      }
    }

    put_block(gameInfo);
  }
}

int allow_rotate(GameInfo_t *gameInfo, int tmp[BLOCK_SIZE][BLOCK_SIZE]) {
  int flag = 0;
  int bad[BLOCK_SIZE][BLOCK_SIZE];
  int left_idx = update_block_col_left(bad);
  int right_idx = update_block_col_right(bad);

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      bad[i][j] = tmp[BLOCK_SIZE - j - 1][i];
    }
  }

  if (gameInfo->block_col + right_idx > 7 ||
      gameInfo->block_col - left_idx > -2) {
    flag = 1;
  }

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_SIZE; ++j) {
      if (bad[i][j] == 1) {
        if (gameInfo->field[gameInfo->block_row + i][gameInfo->block_col + j] ==
                2 ||
            gameInfo->block_row + j + 1 > HEIGHT) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}

int update_block_col_left(int bad[BLOCK_SIZE][BLOCK_SIZE]) {
  int pos = 2;
  int tmp = 6;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (bad[i][j] == 1 && j < pos && < j < tmp) {
        tmp = j;
      }
    }
  }

  if (tmp == 6) {
    return 0;
  }
  return pos - tmp;
}

int update_block_col_right(int bad[BLOCK_SIZE][BLOCK_SIZE]) {
  int pos = 2;
  int tmp = -1;

  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      if (bad[i][j] == 1 && j > pos && j > tmp) {
        tmp = j;
      }
    }
  }
  if (tmp == -1) {
    return 0;
  }
  return tmp - pos;
}

int check_square(GameInfo_t *gameInfo) {
  if (gameInfo->block[1][2] && gameInfo->block[2][2] && gameInfo->block[1][3] &&
      gameInfo->block[2][3])
    return 0;
  return 1;
}

void freeze_block(GameInfo_t *gameInfo) {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (gameInfo->field[i][j] == 1) {
        // 2 - freeze pixel //
        gameInfo->field[i][j] = 2
      }
    }
  }
}

void find_full_lines(GameInfo_t *gameInfo, int *num) {
  for (int i = HEIGHT - 1; i >= 0; i--) {
    int count = 0;

    for (int j = 0; j < WIDTH; j++) {
      if (gameInfo->field[i][j] != 0) {
        count++;
      }
    }

    if (count == WIDTH) {
      *num += 1;
      clear_lines(game, i);
      find_full_lines(gameInfo, num);
    }
  }
}

void update_score(GameInfo_t *game, int count) {
  int step = 100;
  if (count == 1) {
    game->score += step * count;
  } else if (count == 2) {
    game->score += step * 3;
  } else if (count == 3) {
    game->score += step * 7;
  } else if (count >= 4) {
    game->score += step * 15;
  }
  if (game->score > game->high_score) {
    game->high_score = game->score;
  }
}

void update_speed(GameInfo_t *gameInfo, int **speed) {
  int current_speed = gameInfo->speed;
  int new_speed = gameInfo->score / 600 + 1;

  if (new_speed > 10) {
    new_speed = 10;
  }

  if (new_speed > current_speed) {
    **speed = **speed - (new_speed - current_speed) * 30;
    gameInfo->speed = new_speed;
  }
}

void clear_lines(GameInfo_t *gameInfo, int row_idx) {
  for (int i = row_idx; i > 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      gameInfo->field[i][j] = gameInfo->field[i - 1][j];
    }
  }

  for (int i = 0; i < WIDTH; i++) {
    gameInfo->field[0][i] = 0;
  }
}

void check_finish(GameInfo_t *gameInfo) {
  for (int i = 0; i <= 5; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (gameInfo->field[i][j] == 2) {
        gameInfo->status = GameOver;
      }
    }
  }
}

GameInfo_t update_current_state(GameInfo_t *gameInfo, int *move_interval) {
    int count = 0;

    freeze_block(gameInfo);
    find_full_lines(gameInfo, &count);

    if (count > 0) {
        update_score(gameInfo, count);
        update_speed(gameInfo, &move_interval);
    }

    check_finish(gameInfo);

    if (gameInfo->status != GameOver) {
        gameInfo->block_row = 0;
        gameInfo->block_col = 2;
        gameInfo->status = Down;
        choice_tetromino(gameInfo);
        put_block(gameInfo);
    }
    return *gameInfo;
}