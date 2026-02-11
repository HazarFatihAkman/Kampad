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

void set_raw_mode(int enable) {
  if (enable == 1) {
    struct termios raw = orig_t;
    raw.c_lflag &= ~ (ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
  }
  else {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_t);
  }
}

void relocate_cursor(int row, int column) {
  if ((row < 0 && row > kampad_f.buffer.rows.count)
    || column < 0) {
    return;
  }

  if (kampad_f.buffer.current_row != row && row < kampad_f.buffer.rows.count) {
    kampad_f.buffer.current_row = row;
    printf("\nrow %d\n", kampad_f.buffer.current_row);
    fflush(stdout);
    return;
  }

  rows_t rows = kampad_f.buffer.rows;
  row_t *selected_row = (row_t*)rows.items[row];
  if (selected_row->current_column != column && column < selected_row->current_column) {
    selected_row->current_column = column;
    printf("\ncolumn : %d\n", selected_row->current_column);
    fflush(stdout);
    kampad_f.buffer.rows = rows;
    return;
  }
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

  row_t *selected_row = {0};
  int row = 0;
  int column = 0;
  while(1) {
    c = gchar();
    if (c == 'i' && insert_mode == 0) {
      insert_mode = 1;
      set_raw_mode(insert_mode);
      row_t new_row = {
          .index = 0,
          .columns = 0,
          .current_column = 0
      };
      push_v((void*)&new_row, &kampad_f.buffer.rows);
      selected_row = (row_t*)kampad_f.buffer.rows.items[kampad_f.buffer.current_row];
    }
    else if (c == 27 && insert_mode == 1) {
      char seq[2];
      if (read(STDIN_FILENO, &seq[0], 1) == 1
       && read(STDIN_FILENO, &seq[1], 1) == 1) {
        switch (seq[1]) {
          case 0x41: row = kampad_f.buffer.current_row + 1; break;
          case 0x42: row = kampad_f.buffer.current_row - 1; break;
          case 0x43: column = selected_row->current_column + 1; break;
          case 0x44: column = selected_row->current_column - 1; break;
        }

        relocate_cursor(row, column);
      }
      else {
        insert_mode = 0;
        set_raw_mode(insert_mode);
        break;
      }
    }
    else if (insert_mode == 1) {
      append(&kampad_f.buffer, c);
      printf("%c", c);
      fflush(stdout);
      if (c == 10) {
        row_t new_row = {
          .index = kampad_f.buffer.rows.count,
          .columns = 0,
          .current_column = 0
        };
        push_v((void*)&new_row, &kampad_f.buffer.rows);
      }
      else {
        column = selected_row->columns;
      }
    }
  }
  // if (c == keymapping[1]) {
  //     fprintf(kampad_f.fp, kampad_f.buffer.value);
  // }

  printf("%s\n", kampad_f.buffer.value);
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
