#include "../include/terminal.h"

#include <termios.h>
#include <unistd.h>

uint8_t set_raw_mode(const struct termios t, const uint8_t enabled) {
  if (enabled == 1) {
    struct termios raw = t;
    raw.c_lflag &= ~(ICANON | ECHO);
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

uint8_t refresh_tui(rows_t rows) {
  return 0;
}

char gchar() {
  char c;
  read(STDIN_FILENO, &c, 1);
  return c;
}
