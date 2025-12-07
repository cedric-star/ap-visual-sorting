#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


#define ARR_LENGTH 20
#define MAX_NUM 10

void screenSize() {
  int height;
  int width;

  getmaxyx(stdscr, height, width);

  mvprintw(2, 0, "Screenwidth: %d", width);
  mvprintw(3, 0, "Screenheigth: %d", height);

  refresh();  
}

void readInput() {
  char inp[100];
  mvprintw(4, 0, "Input: ");
  getnstr(inp, 100);

  mvprintw(5, 0, "Output: %s", inp);

  refresh();
}


int main (void) {
  initscr(); //initialise ncurses
  clear(); //delete everything on screen
  cbreak(); //deactivates line buffering (read input without waiting for enter)

  int arr[ARR_LENGTH];


  srand(time(NULL));
  for (int i = 0; i < ARR_LENGTH; i++) {
    arr[i] = floor(rand() % MAX_NUM);
    char str[20];
    sprintf(str, "%d", arr[i]);
    mvaddstr(1, (i*2), str);
  }

  mvaddstr(10, 30, "press any key to quit");

  screenSize();
  readInput();
  
  refresh(); //operations by stdscr() only then visible, for windows: wrefresch(window)
  getch();
  endwin();
  return 0;
}