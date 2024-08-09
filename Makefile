GAME_FILES = brick_game/tetris/*.c brick_game/tetris/*.h
GUI_FILES = gui/cli/*.c gui/cli/*.h
MAIN_FILE = main.c
TESTS_FILE = tests/tests.c
TEST_FLAGS = -fprofile-arcs -ftest-coverage
GCNO_FILES = ./*.gcno

build:
	gcc -o tetris main.c $(GAME_FILES) $(GUI_FILES) -lncurses
	./tetris

test:
	gcc -o tetris_test $(TEST_FLAGS) `pkg-config --cflags --libs check` $(TESTS_FILE) $(GAME_FILES)
	./tetris_test

gcov_report: test
	gcov $(GCNO_FILES) -m
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	genhtml -o ./ gcov_report.info
	open ./index-sort-f.html

clean:
	rm -r tetris tetris_test *.gcno *.gcda *.gcov

clang:
	@clang-format --style=Google -n	$(GAME_FILES) $(GUI_FILES) $(MAIN_FILE) $(TESTS_FILE)

style:
	@clang-format --style=Google -i $(GAME_FILES) $(GUI_FILES) $(MAIN_FILE) $(TESTS_FILE)

