#ifndef CDL_LIBRARY_STRINGS_H
#define CDL_LIBRARY_STRINGS_H

#include <sys/types.h>

typedef struct {
  const char **items;
  size_t count;
  size_t capacity;
} strings;

// push
void _push_s(const char *x, strings *l);
#define str_push(x, l) _push_s(x, l)

// pop
void _pop_s(strings *l);
#define str_pop(l) _pop_s(l)

// remove
void _remove_s(int i, strings *l);
#define str_remove(i, l) _remove_s(i, l)

#endif // CDL_LIBRARY_STRINGS_H
