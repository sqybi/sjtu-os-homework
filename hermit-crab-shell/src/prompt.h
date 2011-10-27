#include "debug.h"

#ifndef __PROMPT_H__
#define __PROMPT_H__

// Get the length of last directory in a directory string.
// The string "dir" is always the return value of getcwd().
int get_last_dir_len(const char *);

// Get the prompt string, and return.
char *get_prompt();

#endif
