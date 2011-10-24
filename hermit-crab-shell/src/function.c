#include <stdlib.h>
#include <string.h>
#include "constant.h"
#include "function.h"

// Get the length of last directory in a directory string.
// The string "dir" is always the return value of getcwd().
int get_last_dir_len(char *dir)
{
    int len, i;

    len = strlen(dir);

    for (i = len - 2; i >= 0; --i)
    {
        if (dir[i] == '/')
        {
            return len - 1 - i;
        }
    }

    return len;
}

// Get the prompt string, and return.
char *get_prompt(void)
{
    unsigned int len, plen;
    char *temp, *prompt;
    int i;

    // error when *dir is NULL (should NEVER happen)
    if (*prompt == NULL)
        return NULL;

    // get current dir
    temp = get_current_dir_name();

    // get length of last directory and *dir
    len = get_last_dir_len(temp);
    plen = strlen(temp);

    // create prompt string
    prompt = malloc(len + 3);
    for (i = 0; i != len; ++i)
    {
        prompt[i] = temp[plen - len + i];
    }
    prompt[len] = '>';
    prompt[len + 1] = ' ';
    prompt[len + 2] = '\0';

    return prompt;
}

// Split an input command into COMMAND_LIST type
COMMAND_LIST split_command(char *cmd)
{
    COMMAND_LIST cmd_list;

    return cmd_list;
}

//
