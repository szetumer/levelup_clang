#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 5){
        printf("you must give four int arguments to start with.");
        exit(1);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    int d = atoi(argv[4]);
    initscr();
    WINDOW * win = newwin(a, b, c, d);
    //a = distance from left boarder in ?character spaces?
    //b = alone, increasing this does nothing.
    /// 0 0 0 0 --> a "full box"
    /// x 0 0 0 --> box that is x-1 rows in height from the top; full width.
    /// x y 0 0 --> box x-1 rows in height, y spaces wide.
    /// x y a 0 --> box x-1 rows in height, y spices wide, a rows from the top.
    /// x y a b --> x ~ height; y = width; a = rows downset; b = spaces from left margin.
    box(win,0,0);
    wmove(win, 1, 1);
    waddstr(win, "THIS IS A CURSOR PRINT OVER 20 CHARACTERS LONG");
    //this automatically wraps if you don't have enough space.
    wrefresh(win);

    wgetch(win);
    endwin();
    printf("%d; %d; %d; %d;\n", a, b, c, d);
    fflush(stdout);
    return 0;
}