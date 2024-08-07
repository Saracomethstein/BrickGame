#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 10
#define BLOCK_SIZE 4

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
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int status;

} GameInfo_t;

void user_input(UserAction_t action, bool hold);
GameInfo_t init_game();
GameInfo_t update_current_state();

#endif