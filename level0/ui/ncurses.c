#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "ncurses.h"

char bytespace[4];

int init_window(){
    initscr();
    if(has_colors() == FALSE){
        printf("your terminal doesn't have colors.\n");
        exit(1);
    }
    start_color();
    noecho();
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    return 1;
}

void goto_nextline(WINDOW* win){
    int cury = getcury(win);
    if(cury + 1 >= getmaxy(win) - 1){
        cury = 0;
    }
    wmove(win, cury + 1, getcurx(win));
}

int inloop_movecursor(WINDOW* win, int keystroke){
    int xpos, ypos;
    int xmax, ymax;
    xpos = getcurx(win);
    ypos = getcury(win);
    switch(keystroke){
        case(KEY_UP): {wmove(win, ypos - 1, xpos); break;}
        case(KEY_DOWN): {wmove(win, ypos + 1, xpos); break;}
        case(KEY_RIGHT): {wmove(win, ypos, xpos + 1); break;}
        case(KEY_LEFT): {wmove(win, ypos, xpos - 1); break;}
        default: break;
    }
    switch((char)keystroke){
        case('\n'): {wmove(win, ypos + 1, 1); break;}
        case('a'): {waddch(win, 'a' | A_UNDERLINE); break;}
        case('b'): {waddch(win, 'b' | COLOR_PAIR(1)); break;}
        case('.'): {waddstr(win, "\b."); break;}
        default: break;
    }
    return keystroke;
}

void print_byte(WINDOW* win, void* mem){
    wprintw(win, "%02x ",  *(unsigned char*)mem);
    //waddstr(win, bytespace);
    return;
}

void adjust_cursor_if_noroom(WINDOW* win, int requiredroom){
    int xmax, ymax, y, x;
    xmax = getmaxx(win);
    ymax = getmaxy(win);
    x = getcurx(win);
    y = getcury(win);
    if(x + requiredroom > xmax - 1){
        if(y + 1 >= ymax - 1){
            wmove(win, 1, 1);
            return;
        }
        wmove(win, y + 1, 1);
        return;
    }
    return;
}

void print_byteblock(WINDOW* win, void* mem, int bytecount){
    int total_requirement = 3*bytecount;
    adjust_cursor_if_noroom(win, total_requirement);
    for(int i = 0; i < bytecount; i++){
        print_byte(win, mem);
        adjust_cursor_if_noroom(win, 4);
        mem += 1;
    }
    wprintw(win, "\b.");
}
