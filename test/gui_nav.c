#include "../include/input.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

struct termios t;
uint8_t raw_mode_active = 0;
void set_raw_mode(int enable) {
  if (enable == 1) {
    struct termios raw = t;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    printf("Insert Mode Enabled\r\n--------");
    fflush(stdout); 
  }
  else {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
  }
  raw_mode_active = enable;
}

void refresh_gui(char *buffer, int s_i) {
  printf("\r\033[u\033[2K");
  for (int i = 0; i < strlen(buffer); i++) {
    if (i == s_i) {
      printf("\033[37;100m%c\033[0m", buffer[i]);
    }
    else {
      printf("%c", buffer[i]);
    }
  }
  fflush(stdout);
}

// TODO: rows are the char* lines of buffer.
//       columns are the char of lines.

// TODO: get row location and also column location
//       for assigning the correct row-column index.

// TODO: find a solution of the new line issue.
//       that should be bellow the insert mode enabled.
//       but it's too away from the output.

void create_row();
void create_column();

int main(int argv, char *args[]) {
  tcgetattr(STDIN_FILENO, &t);
  char *buffer = (char*)malloc(1024);
  if (buffer == NULL) return 0;

  int i = 0;
  int s_i = 0;
  char c;
  while (1) {
    c = gchar();
    if (c == 'i' && raw_mode_active == 0) {
      set_raw_mode(1);
    }
    else if (c == 27 && raw_mode_active == 1) {
      set_raw_mode(0);
      break;
    }
    else if (c != '\n') {
      buffer[i] = c; 
      s_i = i;
      i++;
      refresh_gui(buffer, s_i);
    }
}

  return 0;
}
