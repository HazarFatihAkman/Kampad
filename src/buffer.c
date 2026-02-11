#include "../include/buffer.h"

#include <stdio.h>
#include <stdlib.h>

void append(buffer_t *self, char c) {
  self->size++;
  if (self->size > self->capacity) {
    self->capacity *= 2;
  }

  self->value = (char*) realloc(self->value, self->size);
  self->value[self->size-1] = c;
  self->value[self->size] = '\0';
}


