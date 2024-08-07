#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 10
#define BLOCK_SIZE 5
#define TETROMINO_COUNT 7

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int x;
  int y;
  int shape;
  int rotation;
} Tetromino;

typedef struct {
  int **field;
  int **next;
  int **block;
  int block_row;
  int block_col;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int status;
} GameInfo_t;

// tetromino figure //
int tetrominos[TETROMINO_COUNT][BLOCK_SIZE][BLOCK_SIZE] = {
    {{0, 0, 0, 0, 0},
     {0, 1, 0, 0, 0},
     {0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0},
     {0, 0, 0, 1, 0},
     {0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0},
     {0, 0, 1, 1, 0},
     {0, 0, 1, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0},
     {0, 0, 1, 1, 0},
     {0, 1, 1, 0, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    {{0, 0, 0, 0, 0},
     {0, 1, 1, 0, 0},
     {0, 0, 1, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}},

    {{0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 0, 0, 0}},
};

void user_input(UserAction_t action, bool hold);
void choice_tetramino(GameInfo_t *gameInfo);
void put_block(GameInfo_t *gameInfo);
void clear_block(GameInfo_t *gameInfo);

GameInfo_t init_game();
GameInfo_t update_current_state();

#endif