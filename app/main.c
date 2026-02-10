#include "../include/keymapping.h"
#include "../include/input.h"
#include "../include/flags.h"
#include "../include/files.h"

#include <curses.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

char keymapping[KEYMAPPING_SIZE];
flag_t flag = {0};
kampad_file_t kampad_f = {0};
struct termios orig_t;

void enable_raw_mode(struct termios *orig_t) {
  struct termios raw = *orig_t;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disable_raw_mode(struct termios *orig_t) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_t);
}

int main(int argv, const char *args[]) {
  tcgetattr(STDIN_FILENO, &orig_t);
  printf("Welcome Kampad!\n");
  set_keymapping();
  print_keymapping();

  init_flag(&flag, args);
  preload_mode(flag, &kampad_f);

  uint8_t insert_mode = 0;
  char c;
  int selected_i = 0;
  while(1) {
    c = gchar();

    if (c == 'i' && insert_mode == 0) {
      enable_raw_mode(&orig_t);
      insert_mode = 1;
    }
    else if (c == 27 && insert_mode == 1) { 
      char seq[2];

      if (read(STDIN_FILENO, &seq[0], 1) == 1
          && read(STDIN_FILENO, &seq[1], 1) == 1) {
        if (seq[0] == 0x5B) {
          switch (seq[1]) {
            case 0x41: printf("UP "); break;
            case 0x42: printf("DOWN "); break;
            case 0x43: printf("RIGHT "); break;
            case 0x44: printf("LEFT "); break;
          }
        }
        else {
          disable_raw_mode(&orig_t);
          insert_mode = 0;
        }
      }
    }
    // if (insert_mode == 1) {
    //   if (c == 37 && selected_i <= 0) {
    //     selected_i -= 1;
    //   }
    //   else {
    //     append(&kampad_f.buffer, c);
    //   }
    // }
    // else if (c == (char)27 && insert_mode == 1) {
    //   insert_mode = 0;
    //   set_mode(insert_mode);
    // }
    
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

//
// int main() {
//     const char *options[] = {"Open File", "Settings", "Exit"};
//     int selected = 0;
//     char ch;
//
//     set_mode(0);
//
//     while (1) {
//         printf("\033[H\033[J"); 
//         printf("--- MENU NAVIGATOR ---\n");
//
//         for (int i = 0; i < 3; i++) {
//             if (i == selected) {
//                 printf("\033[7m > %s \033[0m\n", options[i]);
//             } else {
//                 printf("   %s \n", options[i]);
//             }
//         }
//
//         ch = getchar();
//
//         if (ch == 'w' && selected > 0) selected--;
//         if (ch == 's' && selected < 2) selected++;
//         if (ch == '\n') break; 
//         if (ch == 'q') break;
//     }
//
//     set_mode(1);
//     printf("\nSelected: %s\n", options[selected]);
//
//     return 0;
// }
