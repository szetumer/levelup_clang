CC = gcc

hello_world: hello_world.c 
	$(CC) -o hello_world hello_world.c -lncurses -lpanel

create_window: create_window.c
	$(CC) -o create_window create_window.c -lncurses -lpanel

move_cursor: move_cursor.c
	$(CC) -o move_cursor move_cursor.c -lncurses -lpanel

basictext_ui: basictext_ui.c ncurses.c
	$(CC) -o basictext_ui basictext_ui.c ncurses.c -lncurses -lpanel