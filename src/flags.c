#include "../include/flags.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_flag(flag_t *flag, const char *args[]) {
  flag->mode = args[1] != NULL && strcmp(args[1], CREATE_FLAG) == 0
    ? CREATION : EDIT;

  int filename_index = strlen(args[1]) == 2 ? 2 : 1;
  if (args[filename_index] != NULL) {
    flag->filename = (char*) malloc(strlen(args[filename_index]));
    if (flag->filename == NULL) {
      return;
    }

    strcpy(flag->filename, args[filename_index]);
  } 
}

void preload_mode(flag_t flag, kampad_file_t *out) {
  if (flag.mode == CREATION) {
    out->filename = (char*) malloc(strlen(flag.filename));
    if (out->filename == NULL) {
      printf("Memory Allocation!\n");
      return;
    }

    strcpy(out->filename, flag.filename);
    if (create_file(out) == 0) {
      printf("File creation failed! %s\n", out->filename);
      return;
    }
    else {
      printf("File creation successfully! - %s\n", out->filename);
      return;
    }
  }
  else {
    //TODO : read file and set content to untouched buffer
  }
} 

