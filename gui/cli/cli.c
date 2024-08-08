#include "cli.h"

void init_curses() {
  initscr();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  raw();
  noecho();
  cbreak();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_GREEN);
  init_pair(3, COLOR_RED, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_BLACK);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  init_pair(6, COLOR_YELLOW, COLOR_BLACK);
}

WinStruct *init_windows() {
  WinStruct *window = (WinStruct *)malloc(sizeof(WinStruct));
  if (window == NULL) {
    return NULL;
  }
  window->field = newwin(22, 22, 2, 14);
  window->stats = newwin(6, 20, 2, 36);
  window->next = newwin(7, 14, 8, 36);
  window->help = newwin(9, 20, 15, 36);
  return window;
}

void draw_board(GameInfo_t *game, WINDOW *window) {
  box(window, 0, 0);
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      if (game->field[row][col] == 0) {
        mvwprintw(window, row + 1, 2 * col + 1, "%c", ' ');
        mvwprintw(window, row + 1, 2 * col + 2, "%c", ' ');
      } else if (game->field[row][col] == 1) {
        mvwprintw(window, row + 1, 2 * col + 1, "[");
        mvwprintw(window, row + 1, 2 * col + 2, "]");
      } else if (game->field[row][col] == 2) {
        mvwprintw(window, row + 1, 2 * col + 1, "[");
        mvwprintw(window, row + 1, 2 * col + 2, "]");
      }
    }
  }
  wrefresh(window);
}

void draw_stats(GameInfo_t *game, WINDOW *stats) {
  werase(stats);
  box(stats, 0, 0);
  mvwprintw(stats, 1, 1, "Stats");
  mvwprintw(stats, 2, 1, "Record: %d", game->high_score);
  mvwprintw(stats, 3, 1, "Score: %d", game->score);
  mvwprintw(stats, 4, 1, "Level: %d", game->level);
  wrefresh(stats);
}

void draw_next(GameInfo_t *game, WINDOW *next) {
  werase(next);
  box(next, 0, 0);
  wbkgd(next, COLOR_PAIR(6));
  for (int row = 0; row < BLOCK_SIZE - 1; row++) {
    for (int col = 0; col < BLOCK_SIZE; col++) {
      if (game->next[row][col] == 1) {
        mvwprintw(next, row + 1, 2 * col + 2, "[");
        mvwprintw(next, row + 1, 2 * col + 3, "]");
      } else {
        mvwprintw(next, row + 1, 2 * col + 2, " ");
        mvwprintw(next, row + 1, 2 * col + 3, " ");
      }
    }
  }
  wrefresh(next);
}

void draw_help(WINDOW *help) {
  werase(help);
  box(help, 0, 0);
  mvwprintw(help, 1, 1, "Help");
  mvwprintw(help, 2, 1, "Left:      [<]");
  mvwprintw(help, 3, 1, "Right:     [>]");
  mvwprintw(help, 4, 1, "Down:      [v]");
  mvwprintw(help, 5, 1, "Rotate:    [space]");
  mvwprintw(help, 6, 1, "Quit:      [q]");
  mvwprintw(help, 7, 1, "Pause:     [p]");
  wrefresh(help);
}

void draw_pause(WinStruct *window) {
  wbkgdset(window->field, COLOR_PAIR(4));
  mvwprintw(window->field, 10, 8, "PAUSE");
  wrefresh(window->field);
  nodelay(stdscr, FALSE);
  getch();
  nodelay(stdscr, TRUE);
}

void draw_game_over(WinStruct *window) {
  wbkgdset(window->field, COLOR_PAIR(4));
  mvwprintw(window->field, 10, 8, "GAME OVER");
  mvwprintw(window->field, 11, 1, "Press [r] to restart");
  wrefresh(window->field);
  nodelay(stdscr, false);
  getch();
  nodelay(stdscr, true);
}

void draw_hello(WinStruct *window) {
  wbkgdset(window->field, COLOR_PAIR(4));
  mvwprintw(window->field, 10, 8, "Hello!");
  mvwprintw(window->field, 11, 5, "Press any key");
  mvwprintw(window->field, 12, 6, "to continue.");
  wrefresh(window->field);
  nodelay(stdscr, false);
  getch();
  nodelay(stdscr, false);
}

// check game status for draw boards //
void draw_frontend(GameInfo_t *game, WinStruct *window) {
  if (game->status == Start) {
    draw_board(game, window->field);
    draw_stats(game, window->stats);
    draw_next(game, window->next);
    draw_help(window->help);
    mvwprintw(window->field, 11, 5, "Press any key");
    mvwprintw(window->field, 12, 6, "to continue.");
    wrefresh(window->field);
    int ch = getchar();
    (void)ch;
    nodelay(window->field, true);
    game->status = Down;
  }

  draw_board(game, window->field);
  draw_stats(game, window->stats);
  draw_next(game, window->next);
  draw_help(window->help);

  if (game->status == Pause) {
    draw_pause(window);
  } else if (game->status == GameOver) {
    draw_game_over(window);
  } else if (game->status == Hello) {
    draw_hello(window);
  }
}
