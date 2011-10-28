#include "debug.h"

// define _GNU_SOURCE for get_current_dir_name() function
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifdef DEBUG
#include <stdio.h>
#endif
#include "prompt.h"

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
char *get_prompt()
{
    unsigned int len, plen;
    char *prompt;

    // get current dir
    prompt = get_current_dir_name();
#ifdef DEBUG
    fprintf(stderr, "[prompt.c] The whole dir is \"%s\"\n", prompt);
#endif

    // get length of last directory and *dir
    len = get_last_dir_len(prompt);
    plen = strlen(prompt);

    // create prompt string
    strcpy(prompt, prompt + plen - len);
    prompt = realloc(prompt, len + 3);
    prompt[len] = '>';
    prompt[len + 1] = ' ';
    prompt[len + 2] = '\0';

    return prompt;
}
