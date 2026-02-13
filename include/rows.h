#ifndef KAMPAD_ROWS_H
#define KAMPAD_ROWS_H

#include "../lib/cdl/listInterface.h"

// rows are stored as pointers. 
typedef li_t rows_t;

typedef struct line {
  size_t size;
  char *value;
} line_t;

typedef struct row {
  int index;
  line_t line;
} row_t;

void push_row(const line_t line, rows_t *out);

#endif //KAMPAD_ROWS_H
 
