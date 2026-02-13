#include "../include/rows.h"

void push_row(const line_t line, rows_t *out) {
  row_t new_row = {
    .index = out->count,
    .line = line
  };

  push_v((void*)&new_row, out);
}

