#ifndef __PARSER_H__
#define __PARSER_H__

#include "debug.h"

#include "tokens.h"
#include "command.h"

// errors when parse
typedef enum parse_status
{
    PARSE_STATUS_NORMAL, // parse successfully
    PARSE_STATUS_COMMAND_EXPECTED, // no command between two connecotrs
    PARSE_STATUS_FILENAME_EXPECTED, // not a filename after >, <, etc.
    PARSE_STATUS_FILE_NOT_EXIST, // reading from a file, but file not exist
    PARSE_STATUS_ILLEGAL_CONNECTOR // an illegal connector at the end of command
} PARSE_STATUS;

// check if token is a connector
int is_connector(TOKEN *);

// parse the whole token list
PARSE_STATUS parse(TOKEN_LIST_NODE *);

// parse connectors (| and ;)
PARSE_STATUS parse_connector(TOKEN_LIST_NODE *, TOKEN_LIST_NODE *);

// parse command to run
PARSE_STATUS parse_command(TOKEN_LIST_NODE *, TOKEN_LIST_NODE *);

#endif
