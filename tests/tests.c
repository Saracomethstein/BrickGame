#include <check.h>
#include <stdio.h>

#include "../brick_game/tetris/tetris.h"

START_TEST(init_game_test) {
  GameInfo_t *game = init_game();
  ck_assert_int_eq(game->status, Start);
  user_input(game, ' ');
  ck_assert_int_eq(game->status, Rotation);
  user_input(game, KEY_DOWN);
  ck_assert_int_eq(game->status, Down);
  user_input(game, KEY_LEFT);
  ck_assert_int_eq(game->status, Left);
  user_input(game, KEY_RIGHT);
  ck_assert_int_eq(game->status, Right);
  user_input(game, 'p');
  ck_assert_int_eq(game->status, Pause);
  game->status = Terminate;
  free_game(game);
}
END_TEST

START_TEST(load_game_test) {
  GameInfo_t *game = init_game();
  ck_assert_int_eq(game->block_col, 2);
  ck_assert_int_eq(game->block_row, 0);
  ck_assert_int_eq(game->speed, 1);
  ck_assert_int_eq(game->score, 0);
  free_game(game);
}
END_TEST

START_TEST(choice_tetromino_test) {
  GameInfo_t *game = init_game();
  bool answer = false;
  choose_tetromino(game);
  for (int id = 0; id < TETRAMINO_COUNT; ++id) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
      for (int j = 0; j < BLOCK_SIZE; ++j) {
        if (game->block[i][j] == tetromino[id][i][j]) {
          answer = true;
        }
      }
    }
  }
  ck_assert_int_eq(true, answer);
  free_game(game);
}
END_TEST

START_TEST(place_block_test) {
  GameInfo_t *game = init_game();
  bool answer = false;

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_SIZE; ++j) {
      game->block[i][j] = tetromino[1][i][j];
    }
  }

  place_block(game);

  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      if (game->field[i][j] == 1) {
        answer = true;
      }
    }
  }

  ck_assert_int_eq(true, answer);
  free_game(game);
}
END_TEST

START_TEST(clear_block_test) {
  GameInfo_t *game = init_game();
  bool answer = false;

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_SIZE; ++j) {
      game->block[i][j] = tetromino[1][i][j];
    }
  }

  place_block(game);
  clear_block(game);

  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      if (game->field[i][j] == 0) {
        answer = true;
      }
    }
  }

  ck_assert_int_eq(true, answer);
  free_game(game);
}

START_TEST(move_right_test) {
  GameInfo_t *game = init_game();
  int new_col = game->block_col + 1;
  move_right(game);
  ck_assert_int_eq(new_col, game->block_col);
  free_game(game);
}
END_TEST

START_TEST(move_left_test) {
  GameInfo_t *game = init_game();
  int new_col = game->block_col - 1;
  move_left(game);
  ck_assert_int_eq(new_col, game->block_col);
  free_game(game);
}
END_TEST

START_TEST(move_down_test) {
  GameInfo_t *game = init_game();
  int new_row = game->block_row + 1;
  move_down(game);
  ck_assert_int_eq(new_row, game->block_row);

  game->block_row = 18;
  move_down(game);
  ck_assert_int_eq(game->status, Sig);
  free_game(game);
}
END_TEST

START_TEST(rotate_figure_test) {
  GameInfo_t *game = init_game();
  bool answer = false;

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_SIZE; ++j) {
      game->block[i][j] = tetromino[6][i][j];
    }
  }

  rotate_figure(game);
  rotate_figure(game);

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_SIZE; ++j) {
      if (game->block[i][j] == tetromino[6][i][j]) {
        answer = true;
      }
    }
  }

  ck_assert_int_eq(true, answer);
  free_game(game);
}
END_TEST

START_TEST(update_score_test) {
  GameInfo_t *game = init_game();
  update_score(game, 1);
  ck_assert_int_eq(game->score, 100);
  game->score = 0;

  update_score(game, 2);
  ck_assert_int_eq(game->score, 300);
  game->score = 0;

  update_score(game, 3);
  ck_assert_int_eq(game->score, 700);
  game->score = 0;

  update_score(game, 4);
  ck_assert_int_eq(game->score, 1500);
  game->score = 0;
  free_game(game);
}
END_TEST

START_TEST(update_current_test) {
  GameInfo_t *game = init_game();
  int move_interval = 400;

  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < WIDTH; j++) {
      game->field[i][j] = 1;
    }
  }

  *game = update_current_state(game, &move_interval);

  ck_assert_int_eq(game->score, 1500);
  ck_assert_int_eq(game->speed, 3);
  ck_assert_int_eq(game->level, 3);
  ck_assert_int_eq(game->block_row, 0);
  ck_assert_int_eq(game->block_col, 2);
  ck_assert_int_eq(game->status, Down);

  free_game(game);
}
END_TEST

START_TEST(user_input_test) {
  GameInfo_t *game = init_game();

  user_input(game, 'q');
  ck_assert_int_eq(game->status, Terminate);

  user_input(game, 'r');
  ck_assert_int_eq(game->status, Restart);

  user_input(game, 0);
  ck_assert_int_eq(game->status, Down);

  game->status = Pause;
  user_input(game, 'p');
  ck_assert_int_eq(game->status, Sig);

  free_game(game);
}
END_TEST

START_TEST(record_test) {
  GameInfo_t *game = init_game();

  game->high_score = 1000;
  write_record(game);
  load_record(game);

  ck_assert_int_eq(game->high_score, 1000);
  free_game(game);
}
END_TEST

START_TEST(check_finish_test) {
  GameInfo_t *game = init_game();
  game->field[1][1] = 2;

  check_finish(game);
  ck_assert_int_eq(game->status, GameOver);
  free_game(game);
}
END_TEST

START_TEST(allow_rotation_test) {
  GameInfo_t *game = init_game();
  int answer = 0;

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_SIZE; ++j) {
      game->block[i][j] = tetromino[6][i][j];
    }
  }
  game->block_col = 14;
  answer = allow_rotation(game, game->block);
  ck_assert_int_eq(answer, 1);

  game->block_col = 0;
  game->block_row = 16;
  answer = 0;
  answer = allow_rotation(game, game->block);
  ck_assert_int_eq(answer, 1);
  free_game(game);
}
END_TEST

Suite *brick_game_tests() {
  Suite *tetris = suite_create("tetris");
  TCase *tetris_tests = tcase_create("TETRIS");

  tcase_add_test(tetris_tests, init_game_test);
  tcase_add_test(tetris_tests, load_game_test);
  tcase_add_test(tetris_tests, choice_tetromino_test);
  tcase_add_test(tetris_tests, place_block_test);
  tcase_add_test(tetris_tests, clear_block_test);
  tcase_add_test(tetris_tests, move_right_test);
  tcase_add_test(tetris_tests, move_left_test);
  tcase_add_test(tetris_tests, move_down_test);
  tcase_add_test(tetris_tests, rotate_figure_test);
  tcase_add_test(tetris_tests, update_score_test);
  tcase_add_test(tetris_tests, update_current_test);
  tcase_add_test(tetris_tests, user_input_test);
  tcase_add_test(tetris_tests, record_test);
  tcase_add_test(tetris_tests, check_finish_test);
  tcase_add_test(tetris_tests, allow_rotation_test);

  suite_add_tcase(tetris, tetris_tests);
  return tetris;
}

int main() {
  Suite *tetris = brick_game_tests();
  SRunner *tetris_runner = srunner_create(tetris);
  float number_failed;
  srunner_run_all(tetris_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(tetris_runner);
  srunner_free(tetris_runner);
  return number_failed == 0 ? 0 : 1;
}
