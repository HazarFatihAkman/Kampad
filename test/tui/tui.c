#include "../../include/terminal.h"
#include "../../include/keymapping.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
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
  tcgetattr(STDIN_FILENO, &t); 
  write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7);
  print_keymapping(insert_mode_enabled);

  line.value = (char*) malloc(DBUFFER_SIZE);
  line.size = 0;
  if (line.value == NULL) return 1;

  rows.count = 0;
  char input;
  while ((input = gchar()) != keymapping[1] || insert_mode_enabled == 1) {
    if ((input == keymapping[0] && insert_mode_enabled == 0)
     || (input == 27 && insert_mode_enabled == 1)) {
      insert_mode_enabled = input == keymapping[0];
      set_raw_mode(t, insert_mode_enabled);
    }
    else if (insert_mode_enabled) {
      if (input == 10 || input == 13) {
        line_t *saved_line = (line_t*) malloc(sizeof(line_t));
        saved_line->size = line.size;
        saved_line->value = (char*) malloc(line.size + 1);
        memcpy(saved_line->value, line.value, line.size);
        saved_line->value[line.size] = '\0';
        push_row(*saved_line, &rows);

        line.size = 0;
        free(saved_line);
        saved_line = NULL;
      }
      else {
        line.value[line.size] = input;
        line.size++;
        if (line.size % DBUFFER_SIZE == 0) {
          line.value = (char*)realloc(line.value, 2*DBUFFER_SIZE);
        }
      }
    }

    refresh_tui(line, rows, insert_mode_enabled); 
    // write(STDOUT_FILENO, "\x1b[2J", 4);
    // write(STDOUT_FILENO, test_buffer, strlen(test_buffer));
    // fsync(STDIN_FILENO);
  }

  return 0;
}

