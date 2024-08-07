GAME_FILES = brick_game/tetris/*.c brick_game/tetris/*.h
GUI_FILES = gui/cli/*.c gui/cli/*.h
MAIN_FILE = main.c

build:
	gcc -o tetris main.c $(GAME_FILES) $(GUI_FILES) -lncurses
	./tetris

clean:
	rm -r tetris

clang:
	@clang-format --style=Google -n	$(GAME_FILES) $(GUI_FILES) $(MAIN_FILE)

style:
	@clang-format --style=Google -i $(GAME_FILES) $(GUI_FILES) $(MAIN_FILE)

