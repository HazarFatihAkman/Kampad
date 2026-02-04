#include "../include/flags.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void init_flag(flag_t *flag, const char *args[]) {
    if (args[1] != NULL && strlen(args[1]) == 2) {
    flag->mode[0] = args[1][0];
    flag->mode[1] = args[1][1];
  }

  if (args[2] != NULL) {
    flag->filename = (char*) malloc(strlen(args[2]));
    if (flag->filename == NULL) {
      return;      
    }

    strcpy(flag->filename, args[2]);
  }
}
