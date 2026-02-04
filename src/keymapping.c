#include "../include/keymapping.h"

#include <stdio.h> 

void set_keymapping(void) {
  FILE *fptr;
  fptr = fopen(KEYMAPPING_FILE, "r");

  int i = 0;
  char c;
  while ((c = fgetc(fptr)) && i < KEYMAPPING_SIZE) {
    if (c != DELIMITER) {
      keymapping[i] = c;
      i++;
    }
  }
}

// enum | key
#define KEYMAPPING_FORMAT "| %s %c "
// void print_keymapping(void) {
//   for (int i = 0; i < KEYMAPPING_SIZE; i++) {
//     printf(KEYMAPPING_FORMAT, KEYMAP_STRS[i], keymapping[i]);
//   }
// }

