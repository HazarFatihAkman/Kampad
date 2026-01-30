#ifndef CDL_LIBRARY_LIST_INTERFACE_H
#define CDL_LIBRARY_LIST_INTERFACE_H

#include <sys/types.h>

typedef struct list_interface {
  void **items;
  size_t count;
  size_t capacity;
} li_t;

void recapacity(li_t *l);
void decapacity(li_t *l);

// push
void _push_v(void *v, li_t *l);
#define push_v(v, l) _push_v(v, l) 

// pop
void _pop_v(li_t *l);
#define pop_v(l) _pop_v(l)

// remove_at
void _remove_at(int i, li_t *l);
#define remove_at(i, l) _remove_at(i, l)

#endif // CDL_LIBRARY_LIST_INTERFACE_H

