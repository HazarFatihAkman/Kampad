#include "../include/keymapping.h"
#include "../include/input.h"
#include "../include/flags.h"

#include <stdio.h>
#include <unistd.h>

char keymapping[KEYMAPPING_SIZE];
flag_t flag = {0};

int main(int argv, const char *args[]) {
  printf("Welcome Kampad!\n");
  set_keymapping();
  init_flag(&flag, args);
  printf("FLAG: %s\nFILENAME: %s\n", flag.mode, flag.filename);
  char c;
  while((c = gchar()) != keymapping[0]) printf("user input : %c\n", c);

  return 0;
}
