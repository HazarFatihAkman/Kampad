#ifndef KAMPAD_TERMINAL_H
#define KAMPAD_TERMINAL_H

#include <termios.h>

int getch(struct termios oldt, struct termios newt);
char *getstr(struct termios oldt, struct termios newt);

#endif //KAMPAD_TERMINAL_H

