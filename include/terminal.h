#ifndef KAMPAD_TERMINAL_H
#define KAMPAD_TERMINAL_H

// TODO: raw and refreshing

#include "rows.h"

#include <termios.h>
#include <stdint.h>

uint8_t set_raw_mode(const struct termios t, const uint8_t enabled);

// body
// path | total size | modify at | created at | navigations 
uint8_t refresh_tui(rows_t rows);
char gchar();

#endif // KAMPAD_TERMINAL_H

