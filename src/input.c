#include "../include/input.h"

#include <unistd.h>
#include <sys/types.h>

char gchar() {
  char c;
  read(STDIN_FILENO, &c, 1);
  return c;
}
