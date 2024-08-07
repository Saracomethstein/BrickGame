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
  GameOver,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Rotation,
  Action,
  Sig,
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

void user_input(GameInfo_t *gameInfo, int hold);
void choice_tetramino(GameInfo_t *gameInfo);

// function for put and clear tetromino in field //
void put_block(GameInfo_t *gameInfo);
void clear_block(GameInfo_t *gameInfo);
void clear_lines(GameInfo_t *game, int row_idx);

// move function for block //
void move_down(GameInfo_t *gameInfo);
void move_left(GameInfo_t *gameInfo);
void move_right(GameInfo_t *gameInfo);

// rotate //
void rotate_termino(GameInfo_t *gameInfo);
int allow_rotate(GameInfo_t *gameInfo, int tmp[BLOCK_SIZE][BLOCK_SIZE]);

int update_block_col_left(int bad[BLOCK_SIZE][BLOCK_SIZE]);
int update_block_col_right(int bad[BLOCK_SIZE][BLOCK_SIZE]);

// check //
int check_square(GameInfo_t *gameInfo);
void check_finish(GameInfo_t *gameInfo);

void freeze_block(GameInfo_t *gameInfo);

void find_full_lines(GameInfo_t *gameInfo, int *num);

void update_score(GameInfo_t *game, int count);
void update_speed(GameInfo_t *game, int **speed);

GameInfo_t init_game();
GameInfo_t update_current_state(GameInfo_t *gameInfo, int *move_interval);

#endif