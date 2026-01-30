#ifndef KAMPAD_NEW_FILE_H
#define KAMPAD_NEW_FILE_H

#include <termios.h>

char *init_new_file(struct termios oldt, struct termios newt);
void create_new_file(const char *fn);

#endif // KAMPAD_NEW_FILE_H

