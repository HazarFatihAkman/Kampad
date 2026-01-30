#ifndef CDL_LIBRARY_NUMBERS_H
#define CDL_LIBRARY_NUMBERS_H

#include <sys/types.h>
#include "listInterface.h"

typedef struct key_value_pair {
  void *key;
  void *value; 
} key_value_t;

typedef li_t key_values;

#endif // CDL_LIBRARY_NUMBERS_H

