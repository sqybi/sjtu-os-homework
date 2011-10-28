#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "debug.h"

// a single comamnd
typedef struct command_info
{
    char *command; // command to run
    char **parameters; // parameters when exec
    char *input_file; // input file redirect
    char *output_file; // output file redirect
    int append_mode;
        // 1 when output file should be opened in append mode,
        // and 0 otherwise
    int background_mode;
        // 1 when program run in background, and 0 otherwise
    int parameters_len; // how many parameters there are
    int output_to_pipe;
        // 1 when output will be redirect to a pipe,
        // and 0 otherwise
    int wait_processes;
        // 1 when need to wait for processes,
        // and 0 otherwise
} COMMAND_INFO;

// initialize a COMMAND_INFO variable
void init_command_info(COMMAND_INFO *);

// free all pointers in a COMMAND_INFO variable
void free_command_info(COMMAND_INFO);

// run a command
void run_command(COMMAND_INFO *);

#endif
