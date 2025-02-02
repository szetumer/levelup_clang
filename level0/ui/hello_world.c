#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

int main(){
    initscr(); // Initialize ncurses
    printw("Hello, world!"); // Print to the ncurses window
    refresh(); // Refresh the screen to display the output
    getch(); // Wait for a key press
    endwin(); // End ncurses mode
    return 0;
}