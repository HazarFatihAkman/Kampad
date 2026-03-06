#include "../include/keymapping.h"

#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char **keymapping_formatted;

// enum | key
#define KEYMAPPING_FORMAT "| %s %c "

void init_keymapping(void) {
  FILE *fptr;
  fptr = fopen(KEYMAPPING_FILE, "r");

  int i = 0;
  char c;
  while ((c = fgetc(fptr)) && i < KEYMAPPING_SIZE) {
    if (c != DELIMITER) {
      keymapping[i] = (char)c;
      i++;
    }
  }

  keymapping_formatted = (char**)calloc(KEYMAPPING_SIZE, 24);
  for (int i = 0; i < KEYMAPPING_SIZE; i++) {
    char *formatted = (char*) malloc(24);
    snprintf(formatted, 24, KEYMAPPING_FORMAT, KEYMAP_STRS[i], keymapping[i]);
    keymapping_formatted[i] = formatted;
  }
}

void print_keymapping(uint8_t insert_mode_enabled) {
  for (int i = 0; i < KEYMAPPING_SIZE; i++) {
    write(STDOUT_FILENO, keymapping_formatted[i], strlen(keymapping_formatted[i])); 
  }

  if (insert_mode_enabled) {
    write(STDOUT_FILENO, "mode enabled", 12);
  }
  write(STDOUT_FILENO, "\r\n", 2);
}


