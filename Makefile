#FLAGS
CC = gcc
FLAGS = -Wall -Wextra -Werror --std=c11
TEST_FLAGS = --coverage -lcheck -lsubunit -lm


#FILES
GAME_FILES = brick_game/tetris/*.c brick_game/tetris/*.h
GUI_FILES = gui/cli/*.c gui/cli/*.h
MAIN_FILE = main.c
TESTS_FILE = tests/tests.c
GCNO_FILES = ./*.gcno

SRCS = $(wildcard brick_game/tetris/*.c tests/*.c)
OBJS = $(SRCS:.c=.o)


all: install

install:
	$(CC) -o tetris main.c $(FLAGS) $(GAME_FILES) $(GUI_FILES) -lncurses
	./tetris

test: $(SRCS)
	$(CC) -o tetris_test $(SRCS) $(TEST_FLAGS) `pkg-config --cflags --libs check`
	./tetris_test

gcov_report: test
	gcov $(GCNO_FILES) -m
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	genhtml -o ./ gcov_report.info
	# open ./index-sort-f.html # for macOS
	cmd.exe /C start ./index-sort-f.html # for windows

clean:
	rm -rf tetris tetris_test *.gcno *.gcda *.gcov *.png *.info *.html *.css tests/*.html brick_game/tetris/*.html

clang:
	@clang-format --style=Google -n	$(GAME_FILES) $(GUI_FILES) $(MAIN_FILE) $(TESTS_FILE)

style:
	@clang-format --style=Google -i $(GAME_FILES) $(GUI_FILES) $(MAIN_FILE) $(TESTS_FILE)

