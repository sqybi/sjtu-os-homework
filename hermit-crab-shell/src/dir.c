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

    path = calloc(sizeof(char), strlen(getenv("PATH")) + 1);
    strcpy(path, getenv("PATH"));
    temp = NULL;

    while ((plen = strlen(path)) != 0)
    {
#ifdef DEBUG
        printf("[dir.c] path = %s\n", path);
#endif
        len = (int) (strstr(path, ":") - path);
#ifdef DEBUG
        printf("[dir.c] len = %d\n", len);
#endif
        temp = calloc(sizeof(char), len + 1);
        strncpy(temp, path, len);
        temp[len] = '\0';
#ifdef DEBUG
        printf("[dir.c] temp = %s\n", temp);
#endif
        strncpy(path, path + len + 1, plen);
#ifdef DEBUG
        printf("[dir.c] path (again) = %s\n", path);
#endif

        full = connect_dir(temp, name);

#ifdef DEBUG
        printf("[dir.c] full = %s\n", full);
#endif

        if (access(full, 0) == 0)
        {
            free(temp);
            free(path);
            return full;
        }

        free(temp);
        free(full);
    }

    free(path);
    return NULL;
}
