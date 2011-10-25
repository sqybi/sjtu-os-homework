#include <stdlib.h>
#include <string.h>
#include "tokens.h"

TOKEN *new_token_string(const char *s)
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_STRING;
    t->t_string.str = malloc(strlen(s) + 1);
    strcpy(t->t_string.str, s);
    return t;
}

TOKEN *new_token_pipe()
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_PIPE;
    return t;
}

TOKEN *new_token_bg()
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_BG;
    return t;
}

TOKEN *new_token_in()
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_IN;
    return t;
}

TOKEN *new_token_out()
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_OUT;
    return t;
}

TOKEN *new_token_next()
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_NEXT;
    return t;
}
