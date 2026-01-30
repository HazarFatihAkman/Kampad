#ifndef CDL_LIBRARY_NUMBERS_H
#define CDL_LIBRARY_NUMBERS_H

#include <sys/types.h>

typedef enum {
  SHORT,
  INT,
  LONG,
  UINT,
  DOUBLE,
  LDOUBLE,
  FLOAT,
} data_types_e;

typedef union {
  short int    *shorts;
  int          *ints;
  long         *longs;
  unsigned int *u_ints;
  double       *doubles;
  long double  *l_doubles;
  float        *floats;
} item_types;

typedef struct {
  item_types   items;
  size_t       count;
  size_t       capacity;
  data_types_e type;
} numbers;

// push
void _push_short (short int x, numbers *l);
void _push_int   (int x, numbers *l);
void _push_long  (long x, numbers *l);
void _push_uint  (unsigned int x, numbers *l);
void _push_d     (double x, numbers *l);
void _push_ld    (long double x, numbers *l);
void _push_f     (float x, numbers *l);

#define n_push(x, l) _Generic((x), \
    short int:    _push_short, \
    int:          _push_int,   \
    long:         _push_long,  \
    unsigned int: _push_uint,  \
    double:       _push_d,     \
    long double:  _push_ld,    \
    float:        _push_f      \
)(x, l)

// pop
void _n_pop     (numbers *l);
#define n_pop(l) _n_pop(l)

// remove
void _n_remove  (int i, numbers *l);
#define n_remove(i, l) _n_remove(i, l)

#endif // CDL_LIBRARY_NUMBERS_H

