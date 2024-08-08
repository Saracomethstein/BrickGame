#ifndef DISPLAY_H
#define DISPLAY_H

#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/tetris/tetris.h"

typedef struct {
  WINDOW *field;
  WINDOW *stats;
  WINDOW *next;
  WINDOW *help;
} WinStruct;

void init_curses();
void draw_board(GameInfo_t *field, WINDOW *win);
void draw_next(GameInfo_t *game, WINDOW *nextfigure);
void draw_addinfo(GameInfo_t *game, WINDOW *addinfo);
void draw_stats(GameInfo_t *game, WINDOW *stats);
void draw_help(WINDOW *help);
void draw_next(GameInfo_t *game, WINDOW *next);
void draw_gameover(WinStruct *window);
void draw_frontend(GameInfo_t *game, WinStruct *window);
void draw_pause(WinStruct *window);
void draw_pause(WinStruct *window);
WinStruct *init_windows();

#endif
