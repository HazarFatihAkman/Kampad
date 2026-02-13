#ifndef KAMPAD_KEYMAPPING_H
#define KAMPAD_KEYMAPPING_H

#include "../include/terminal.h"

#include <stdint.h>

#define DELIMITER ':' 
#define KEYMAPPING_FILE "keymap.gokturk"
#define KEYMAPPING_SIZE 4

#define FOREACH_KEYMAP_FLAGS(KEYMAP_FLAGS) \
  KEYMAP_FLAGS(INSERT_MODE)      \
  KEYMAP_FLAGS(QUIT)             \
  KEYMAP_FLAGS(SAVE_FILE)        \
  KEYMAP_FLAGS(DONT_SAVE_FILE)   \

#define GENERATE_KEYMAP_FLAG(FLAG) FLAG,
#define GENERETE_KEYMAP_STR(STR) #STR,

typedef enum {
  FOREACH_KEYMAP_FLAGS(GENERATE_KEYMAP_FLAG)
} KEYMAP_FLAGS;

static const char *KEYMAP_STRS[] = {
  FOREACH_KEYMAP_FLAGS(GENERETE_KEYMAP_STR)
};

extern char keymapping[KEYMAPPING_SIZE];
void init_keymapping(void);
void print_keymapping(void);

#endif // KAMPAD_KEYMAPPING_H

