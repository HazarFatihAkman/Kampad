#include "../include/keymapping.h"
#include "../include/input.h"
#include "../include/flags.h"
#include "../include/files.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char keymapping[KEYMAPPING_SIZE];
flag_t flag = {0};
kampad_file_t kampad_f = {0};

int main(int argv, const char *args[]) {
  printf("Welcome Kampad!\n");
  set_keymapping();
  init_flag(&flag, args);

  if (strcmp(flag.mode, CREATE_FLAG) != -1) {
    kampad_f.filename = (char*) malloc(strlen(flag.filename));
    if (kampad_f.filename == NULL) {
      printf("Something gone wrong!\n");
      return 1;
    }

    strcpy(kampad_f.filename, flag.filename);
    if (create_file(&kampad_f) == 0) {
      printf("Create file failed! - %s\n", kampad_f.filename);
      return 1;
    }
    else {
      printf("File created! - %s\n", kampad_f.filename);
    }
  }

  char c;
  while((c = gchar()) != keymapping[0]) printf("user input : %c\n", c);

  fclose(kampad_f.fp);
  return 1;
}
