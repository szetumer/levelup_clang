#ifndef NCURSES_HEADER
#define NCURSES_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int init_window();
int inloop_movecursor(WINDOW* win, int keystroke);
void goto_nextline(WINDOW* win);
void adjust_cursor_if_noroom(WINDOW* win, int requiredroom);
void print_byte(WINDOW* win, void* mem);
void print_byteblock(WINDOW* win, void* mem, int bytecount);
int print_rowofblocks(WINDOW* win, void* mem, int bytecount, int blocksize);
#endif