#ifndef KAMPAD_FLAGS_H
#define KAMPAD_FLAGS_H

#define CREATE_FLAG "-c"
#define MODIFY_FLAG   "-m"

typedef struct flag {
  char mode[2];
  char *filename;
} flag_t;

void init_flag(flag_t *flag, const char *args[]);

#endif // KAMPAD_FLAGS_H

