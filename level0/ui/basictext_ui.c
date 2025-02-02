#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "ncurses.h"

short int mem[128] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};

int main(int argc, char** argv){
    int rows, columns, right_indent, down_indent;
    int input_char;
    if(argc != 5){
        puts("please provide window dimensions, four ints.\n");
        exit(1);
    }
    rows = atoi(argv[1]);
    columns = atoi(argv[2]);
    down_indent = atoi(argv[3]);
    right_indent = atoi(argv[4]);

    init_window();

    WINDOW* win = newwin(rows, columns, down_indent, right_indent);
    keypad(win, TRUE);
    wbkgd(win, COLOR_PAIR(2));
    box(win, 0, 0);
    wmove(win, 1, 1);
    wrefresh(win);

    while((input_char = wgetch(win)) != 'q'){
        inloop_movecursor(win, input_char);
        wrefresh(win);
        print_byteblock(win, mem, 8);
        wrefresh(win);
    }
    endwin();
    return 0;
}