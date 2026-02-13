#include "../include/keymapping.h"
#include "../include/input.h"
#include "../include/flags.h"
#include "../include/files.h"

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

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

int relocate_cursor(int row, int column) {
  if ((row < 0 && row > kampad_f.buffer.rows.count)
    || column < 0) {
    return 0;
  }

  if (kampad_f.buffer.current_row != row) {
    kampad_f.buffer.current_row = row;
    printf("\nrow %d %d\n", kampad_f.buffer.current_row, row);
    fflush(stdout);
    return 1;
  }

  rows_t rows = kampad_f.buffer.rows;
  row_t *selected_row = (row_t*)rows.items[row];
  if (selected_row->current_column != column && column < selected_row->columns) {
    selected_row->current_column = column;
    printf("\ncolumn : %d %d\n", selected_row->current_column, column);
    fflush(stdout);
    kampad_f.buffer.rows = rows;
    return 1;
  }

  return 0;
}

void refresh_gui(buffer_t buffer) {
  for (int i = 0; i < buffer.size; i++) {
    row_t *row = (void*)buffer.rows.items[i];
    if (buffer.current_row == row->index && row->current_column == i) {
      printf("\033[7m%c\033[0m", buffer.value[i]); 
    }
    else {
      printf("%c", buffer.value[i]);
    }
  }

  fflush(stdout);
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
        int temp_row = 0;
        int temp_column = 0;
        switch (seq[1]) {
          case 0x41: temp_row = row - 1; break;
          case 0x42: temp_row = row + 1; break;
          case 0x43: temp_column = column + 1; break;
          case 0x44: temp_column = column - 1; break;
        }

        if (relocate_cursor(temp_row, temp_column) == 1) {
          row = temp_row;
  
void switch_modes(char key, uint8_t insert_mode_enabled, struct termios t) {
  if (key == keymapping[0] && insert_mode_enabled == 0) {
    set_raw_mode(t, insert_mode_enabled);
  }
  else if (key == 27 && insert_mode_enabled == 1) {
    
  }
}        column = temp_column;
        }
      }
      else {
        insert_mode = 0;
        set_raw_mode(insert_mode);
        break;
      }
    }
    else if (insert_mode == 1) {
      append(&kampad_f.buffer, c);
      if (c == 10) {
        row_t new_row = {
          .index = kampad_f.buffer.rows.count,
          .columns = 0,
          .current_column = 0
        };
        push_v((void*)&new_row, &kampad_f.buffer.rows);
        row = new_row.index;
      }
      else {
        selected_row->columns++;
        selected_row->current_column = selected_row->columns;
        column = selected_row->current_column;
        kampad_f.buffer.rows.items[row] = (void*)selected_row;
      }

      refresh_gui(kampad_f.buffer);
    }
  } 

  fclose(kampad_f.fp);
  return 1;
}
