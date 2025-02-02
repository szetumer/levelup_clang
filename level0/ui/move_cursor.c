#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(int argc, char** argv){
    if(argc != 5){
        puts("you must provide 4 numbers when you run.");
    }
    int a, b, c, d;
    int xpos, ypos;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    c = atoi(argv[3]);
    d = atoi(argv[4]);
    initscr();
    noecho();
    WINDOW* win = newwin(a, b, c, d);
    keypad(win, TRUE);
    box(win, 0, 0);
    wmove(win, 1, 1);
    wrefresh(win);
    int ch;
    while((ch = wgetch(win)) != 'q'){
        xpos = getcurx(win);
        ypos = getcury(win);
        switch(ch){
            case(KEY_UP):{wmove(win, ypos - 1, xpos); break;}
            case(KEY_DOWN):{wmove(win, ypos + 1, xpos); break;}
            case(KEY_LEFT):{wmove(win, ypos, xpos - 1); break;}
            case(KEY_RIGHT):{wmove(win, ypos, xpos + 1); break;}
            default: break;
        }
        wrefresh(win);
    }
    endwin();
    printf("%d; %d; %d; %d;\n", a, b, c, d);
    fflush(stdout);
    return 0;
}