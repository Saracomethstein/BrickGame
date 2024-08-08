#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 20
#define TETRAMINO_COUNT 7
#define BLOCK_SIZE 5
#define OKK 0
#define COLLISION 1
#define GAME_OVER 1

extern const int tetromino[TETRAMINO_COUNT][BLOCK_SIZE][BLOCK_SIZE];

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Rotation,
  Sig,
  GameOver,
  Restart,
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int block[BLOCK_SIZE][BLOCK_SIZE];
  int block_row;
  int block_col;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int status;
} GameInfo_t;

void user_input(GameInfo_t *gameInfo, int hold);
void choose_tetromino(GameInfo_t *gameInfo);

// move block //
void move_left(GameInfo_t *gameInfo);
void move_right(GameInfo_t *gameInfo);
void move_down(GameInfo_t *gameInfo);

// block func //
void clear_block(GameInfo_t *gameInfo);
void place_block(GameInfo_t *gameInfo);
void freeze_block(GameInfo_t *gameInfo);
void clear_lines(GameInfo_t *gameInfo, int row_index);

void update_score(GameInfo_t *gameInfo, int count);
void update_speed(GameInfo_t *gameInfo, int **speed);

// SQLite (now .txt) //
void load_record(GameInfo_t *gameInfo);
void write_record(GameInfo_t *gameInfo);

void free_game(GameInfo_t *gameInfo);
void find_fulls(GameInfo_t *gameInfo, int *count);

void check_finish(GameInfo_t *gameInfo);
int check_square(GameInfo_t *gameInfo);

// rotation //
void rotate_figure(GameInfo_t *gameInfo);
int up_block_col_left(int block[BLOCK_SIZE][BLOCK_SIZE]);
int up_block_col_right(int block[BLOCK_SIZE][BLOCK_SIZE]);
int allow_rotation(GameInfo_t *gameInfo, int block[BLOCK_SIZE][BLOCK_SIZE]);

GameInfo_t *init_game();
GameInfo_t update_current_state(GameInfo_t *gameInfo, int *move_interval);

#endif