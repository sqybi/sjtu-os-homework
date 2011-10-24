#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "datastructure.h"

// Get the length of last directory in a directory string.
// The string is always the return value of getcwd().
int get_last_dir_len(char *);

// Get the prompt string, and return.
char *get_prompt(void);

// Split an input command into COMMAND_LIST type
COMMAND_LIST split_command(char *);

#endif
