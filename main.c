#include "brick_game/tetris/tetris.h"
#include "gui/cli/cli.h"

int main() {
  GameInfo_t *game = init_game();
  init_curses();
  WinStruct *window = init_windows();
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  long last_time = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
  int move_interval = 400;
  while (game->status != Terminate) {
    draw_frontend(game, window);
    int ch = getch();
    user_input(game, ch);
    if (game->status != Sig) {
      clock_gettime(CLOCK_MONOTONIC, &ts);
      long current_time = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
      if (current_time - last_time >= move_interval) {
        move_down(game);
        last_time = current_time;
      }
    }

    if (game->status == Restart) {
      draw_frontend(game, window);
      load_game(game);
    }

    if (game->status == Sig) {
      *game = update_current_state(game, &move_interval);
      if (game->score == game->high_score) {
        write_record(game);
      }
      if (game->status == GameOver) {
        draw_frontend(game, window);
        int c = getch();

        if (c == 'q') {
          game->status = Terminate;
        }

        if (c == 'r') {
          game->status = Restart;
        }
      }
    }
  }
  endwin();
  free_game(game);
  free(window);
  return 0;
}
