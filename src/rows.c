#include "../include/rows.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void push_row(const line_t line, rows_t *out) {
  row_t *new_row = (row_t*) malloc(sizeof(row_t));
  if (new_row == NULL) return;

  new_row->index = out->count;
  new_row->line = line;

  push_v((void*)new_row, out);
}

