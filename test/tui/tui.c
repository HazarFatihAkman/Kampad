#include "../../include/terminal.h"
#include "../../include/keymapping.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#define DBUFFER_SIZE 1024

char keymapping[KEYMAPPING_SIZE];
struct termios t;
uint8_t insert_mode_enabled = 0;
line_t line = {0};
rows_t rows = {0};

int main(int argv, char *args[]) {
  init_keymapping();
  print_keymapping();
  tcgetattr(STDIN_FILENO, &t);

  line.value = (char*) malloc(1024);
  line.size = 0;
  if (line.value == NULL) return 1;

  rows.count = 0;
  char input;
  while (1) {
    input = gchar();
    if ((input == keymapping[0] && insert_mode_enabled == 0)
     || (input == 27 && insert_mode_enabled == 1)) {
      insert_mode_enabled = input == keymapping[0];
      set_raw_mode(t, insert_mode_enabled);
    }
    else {
      if (input == '\n') {
        line.value[line.size] = input;
        line.size++;
        line.value[line.size] = '\0';
        line.value = (char*) realloc(line.value, line.size);
        if (line.value == NULL) break;

        push_row(line, &rows); 

        line_t new_line = {0};
        new_line.value = (char*) malloc(1024);
        new_line.size = 0;
        if (new_line.value == NULL) return 1;

        line = new_line; 
      }
      else {
        line.value[line.size] = input;
        line.size++;

        printf("\r\033[2K");
        for (int i = 0; i < rows.count; i++) {
          line_t *line_ptr = (line_t*)rows.items[i];
          printf("%s", line_ptr->value);
        }

        printf("%s", line.value);
        fflush(stdout);
      }
    }
  }

  return 0;
}

