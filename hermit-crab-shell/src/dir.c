#include "debug.h"

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "dir.h"

char *connect_dir(char *first, char *second)
{
    int first_len, second_len, len;
    char *temp;

    first_len = strlen(first);
    second_len = strlen(second);
    len = first_len + second_len;
    if (first[first_len - 1] != '/')
        ++len;

    temp = calloc(sizeof(char), len + 1);
    strcpy(temp, first);
    if (first[first_len - 1] != '/')
        strcat(temp, "/");
    strcat(temp, second);

    return temp;
}

char *check_file_exist(char *name)
{
    char *path, *temp, *full;
    int plen, len;

    path = getenv("PATH");

    while ((plen = strlen(path)) != 0)
    {
        temp = strstr(path, ":");
        if (temp != NULL)
            len = (int) (temp - path);
        else
            len = plen;
        temp = calloc(sizeof(char), len + 1);
        strncpy(temp, path, len);
        temp[len] = '\0';
        path += len + 1;

        full = connect_dir(temp, name);

        if (access(full, 0) == 0)
        {
            free(temp);
            return full;
        }
        else
        {
            free(temp);
            free(full);
        }
    }

    return NULL;
}
