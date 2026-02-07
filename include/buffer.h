#ifndef KAMPAD_BUFFER_H
#define KAMPAD_BUFFER_H

#define CAPACITY 1024

#include <sys/types.h>

typedef struct buffer {
  size_t capacity;
  size_t size;
  char *value;
} buffer_t;

void append(buffer_t *self, char c);
void remove_at(buffer_t *self, int index); // 10 index -> 2 reindex

#endif // KAMPAD_BUFFER_H

