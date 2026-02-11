#ifndef KAMPAD_BUFFER_H
#define KAMPAD_BUFFER_H

#define CAPACITY 1024

#include <sys/types.h>
#include "../lib/cdl/listInterface.h"

typedef struct row {
  int index;
  int columns;
  int current_column;
} row_t;

typedef li_t rows_t;

typedef struct buffer {
  size_t capacity;
  size_t size;
  int current_row;
  rows_t rows;
  char *value;
} buffer_t;

void append(buffer_t *self, char c);
// void remove_at(buffer_t *self, int index); // 10 index -> 2 reindex

#endif // KAMPAD_BUFFER_H

