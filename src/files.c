#include "../include/files.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int create_file(kampad_file_t *kampad_f) {
  kampad_f->fp = fopen(kampad_f->filename, "w");
  if (kampad_f->fp != NULL) {
    return 1;
  }

  return 0;
}

int read_file(kampad_file_t *kampad_f) {
  kampad_f->fp = fopen(kampad_f->filename, "r");
  return 0;
}

int save_file(kampad_file_t *kampad_f) {
  return 0;
}

