#ifndef KAMPAD_FLAGS_H
#define KAMPAD_FLAGS_H

#include "files.h"
#define CREATE_FLAG "-c"

typedef enum {
  FAILED,
  CREATION,
  EDIT
} MODES_E;

typedef struct flag {
  MODES_E mode;
  char *filename;
} flag_t;

void init_flag(flag_t *flag, const char *args[]);
void preload_mode(flag_t flag, kampad_file_t *out);

#endif // KAMPAD_FLAGS_H

