#ifndef __DATASTRUCTURE_H__
#define __DATASTRUCTURE_H__

#include "constant.h"

// token is one word in the command splited by spaces
// something like > < | is also a token
typedef char* TOKEN;

// list of token
typedef struct token_list
{
    TOKEN word;
    struct token_list *next;
} TOKEN_LIST;

// a single command
// including tokens and the connect operator (e.g. | || && etc)
typedef struct command
{
    TOKEN_LIST parameter;
    TOKEN operator;
} COMMAND;

// list of commands
typedef struct command_list
{
    COMMAND command;
    struct command_list *next;
} COMMAND_LIST;

#endif
