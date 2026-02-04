#include "../include/keymapping.h"
#include "../include/terminal.h"
#include "../include/new_file.h"

#include <stdio.h>
#include <unistd.h>

struct termios oldt, newt;
char keymapping[KEYMAPPING_SIZE];

int main(int argv, char *args[]) {
  printf("Welcome Kampad!\n");
  char *file_name = args[1];
  if (file_name == NULL) {
    printf("Nothing selected\n");
  }
  else {
    printf("%s\n", file_name);
  }

  set_keymapping();
  // print_keymapping(); 

  enableRawMode();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != keymapping[0]);

  return 0;
}
