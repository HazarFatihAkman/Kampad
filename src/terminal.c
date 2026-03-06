#include "../include/terminal.h"
#include "../include/keymapping.h"

#include <stdio.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

uint8_t set_raw_mode(const struct termios t, const uint8_t enabled) {
  if (enabled == 1) {
    struct termios raw = t;
    raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
    raw.c_oflag &= ~(OPOST);
    raw.c_iflag &= ~(ICRNL | IXON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    return 1;
  }
  else {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
    return 1;
  }
  return 0;
}

void refresh_tui(line_t current_line, rows_t rows, uint8_t insert_mode_enabled) {
  write(STDOUT_FILENO, "\x1b[2J\x1b[H", 7);
  print_keymapping(insert_mode_enabled);

  for (int i = 0; i < rows.count; i++) {
    line_t *line_ptr = (line_t*)rows.items[i];
    write(STDOUT_FILENO, line_ptr->value, line_ptr->size);
    write(STDOUT_FILENO, "\r\n", 2);
  }

  write(STDOUT_FILENO, current_line.value, current_line.size);
  fsync(STDIN_FILENO);
}

char gchar() {
  char c;
  read(STDIN_FILENO, &c, 1);
  return c;
}
