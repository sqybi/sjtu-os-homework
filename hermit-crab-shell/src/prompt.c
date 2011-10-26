#include <stdlib.h>
#include <string.h>
#include "prompt.h"

// define _GNU_SOURCE for get_current_dir_name() function
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

// Get the length of last directory in a directory string.
// The string "dir" is always the return value of getcwd().
int get_last_dir_len(const char *dir)
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

    if (temp != NULL) free(temp);

    return prompt;
}
