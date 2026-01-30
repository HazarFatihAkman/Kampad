#include "../include/terminal.h"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int getch(struct termios oldt, struct termios newt) {
  int ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_cflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

char *getstr(struct termios oldt, struct termios newt) {
  char *str = (char*) malloc(1024);
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_cflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
  //TODO : it doesn't set the value of terminal
  fgets(str, 1024, stdin);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return str;
}
