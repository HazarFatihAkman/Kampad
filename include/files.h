#ifndef KAMPAD_FILES_H
#define KAMPAD_FILES_H

#include <stdio.h>

typedef struct file {
  FILE *fp;
  char *name;
} file_t;

#endif // KAMPAD_FILES_H

