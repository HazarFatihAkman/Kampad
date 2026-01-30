#include "../include/terminal.h"
#include "../include/keymapping.h"
#include "../include/new_file.h"

#include <stdio.h>

struct termios oldt, newt;
char keymapping[KEYMAPPING_SIZE];

int main(int argv, char *args[]) {
  printf("Welcome Kampad!\n");
  set_keymapping();

  print_keymapping();
  printf("\n");

  char mode = '\0';
  char c;

  while (mode != keymapping[0]) {
    if (mode == '\0') {
      mode = getch(oldt, newt);
    }
    else {
      c = getch(oldt, newt);
    }

    if (mode == 'q') break;
    if (mode == 'i') {
      char *fn = init_new_file(oldt, newt);
      mode = '\0';
    }
  }
  return 0;
}
