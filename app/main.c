#include "../include/keymapping.h"
#include "../include/input.h"
#include "../include/flags.h"
#include "../include/files.h"

#include <curses.h>
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ncurses.h>

char keymapping[KEYMAPPING_SIZE];
flag_t flag = {0};
kampad_file_t kampad_f = {0};
struct termios t;

static void disable_RAWMODE(void) {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t) == -1) {
    perror("error occur in function disable_RAWMODE!");
  }
}

static void enable_RAWMODE(void) {
  struct termios raw;
  if (tcgetattr(STDIN_FILENO, &raw) == -1 || tcgetattr(STDOUT_FILENO, &t) == -1) {
    perror("tcgetattr");
  }

  atexit(disable_RAWMODE);

  raw.c_lflag &= ~(ECHO | ECHOE | ICANON);

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    perror("tcsetattr");
  }
}

int main(int argv, const char *args[]) {
  printf("Welcome Kampad!\n");
  set_keymapping();
  print_keymapping();

  init_flag(&flag, args);
  preload_mode(flag, &kampad_f);

  char c;
  while((c = gchar()) != keymapping[0]) {
    append(&kampad_f.buffer, c);

  }

  while ((c = gchar()) != keymapping[1] && c != keymapping[2]) {
    printf("Wanna save changes?\n");
  }

  if (c == keymapping[1]) {
      fprintf(kampad_f.fp, kampad_f.buffer.value);
  }

  fclose(kampad_f.fp);
  return 1;
}

