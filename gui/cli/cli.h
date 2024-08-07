#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <stdlib.h>

#include "../../brick_game/tetris/tetris.h"

typedef struct {
  WINDOW *win;
  WINDOW *preview;
  WINDOW *addinfo;
} WinStruct;

#endif
