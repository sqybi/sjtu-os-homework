#include <stdlib.h>
#include <string.h>
#include "function.h"

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

int get_last_dir(char **dir)
{
    unsigned int len, dirlen;
    char *tdir;
    int i;

    if (*dir == NULL)
        return -1;

    len = get_last_dir_len(*dir);
    dirlen = strlen(*dir);

    tdir = malloc(len + 3);
    for (i = 0; i != len; ++i)
    {
        tdir[i] = (*dir)[dirlen - len + i];
    }
    tdir[len] = '>';
    tdir[len + 1] = ' ';
    tdir[len + 2] = '\0';

    free(*dir);
    *dir = tdir;

    return 0;
}
