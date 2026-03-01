#ifndef KAMPAD_TERMINAL_H
#define KAMPAD_TERMINAL_H

// TODO: raw and refreshing

#include "rows.h"

#include <termios.h>
#include <stdint.h>

uint8_t set_raw_mode(const struct termios t, const uint8_t enabled);

// body
// path | total size | modify at | created at | navigations 
void refresh_tui(line_t current_line, rows_t rows, uint8_t insert_mode_enabled);
char gchar();

#endif // KAMPAD_TERMINAL_H

