#ifndef KAMPAD_FILES_H
#define KAMPAD_FILES_H

#include <stdio.h>

typedef struct kampad_file {
  FILE *fp;
  char *filename;
  char *buffer;
  char *untouched_buffer;
} kampad_file_t;

int create_file(kampad_file_t *kampad_f);
int read_file(kampad_file_t *kampad_f);
int save_file(kampad_file_t *kampad_f);

#endif // KAMPAD_FILES_H

