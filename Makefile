#FLAGS
CC = gcc
FLAGS = -Wall -Wextra -Werror --std=c11
TEST_FLAGS = --coverage -lcheck -lsubunit -lm


#FILES
GAME_FILES = brick_game/tetris/*.c brick_game/tetris/*.h
GUI_FILES = gui/cli/*.c gui/cli/*.h
MAIN_FILE = main.c
TESTS_FILE = tests/tests.c
GCNO_FILES = ./tests/*.gcno

SRCS = $(wildcard brick_game/tetris/*.c tests/*.c)
OBJS = $(SRCS:.c=.o)


all: install run

run:
	@echo "==> Running the application..."
	@./build/tetris

install:
	@echo "==> Install the application..."
	@mkdir build
	@$(CC) -o build/tetris main.c $(FLAGS) $(GAME_FILES) $(GUI_FILES) -lncurses
	@echo "==> Done."

uninstall:
	@echo "==> Uninstall the application..."
	@rm -rf build
	@echo "==> Done."

dvi:
	@echo "==> Open documentation..."
	@ #open ./docs/documentation.html
	@cmd.exe /C start ./docs/documentation.html

dist: clean
	@tar -czvf tetris.tar.gz . makefile

test: $(SRCS)
	@echo "==> Test the application..."
	@$(CC) -o tests/tetris_test $(SRCS) $(TEST_FLAGS) `pkg-config --cflags --libs check`
	@./tests/tetris_test

gcov_report: test
	@echo "==> Generate test report..."
	@gcov $(GCNO_FILES) -m
	@lcov -t "gcov_report" -o gcov_report.info -c -d .
	@genhtml -o ./ gcov_report.info
	@ #open ./index-sort-f.html # for macOS
	@cmd.exe /C start ./index-sort-f.html # for windows

clean:
	@echo "==> Cleaning up..."
	@rm -rf build tetris tetris_test *.gcno *.gcda *.gcov *.png *.info *.html *.css tests/*.html brick_game/tetris/*.html tetris.tar.gz
	@rm -rf tests/*.gcno tests/*.gcda tests/tetris_test

clang:
	@echo "==> Check Google style..."
	@clang-format --style=Google -n	$(GAME_FILES) $(GUI_FILES) $(MAIN_FILE) $(TESTS_FILE)

style:
	@echo "==> Set Google style..."
	@clang-format --style=Google -i $(GAME_FILES) $(GUI_FILES) $(MAIN_FILE) $(TESTS_FILE)

