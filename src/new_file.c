#include "../include/new_file.h"
#include "../include/terminal.h"

#include <stdio.h>

char *init_new_file(struct termios oldt, struct termios newt) {
  return getstr(oldt, newt);
}

