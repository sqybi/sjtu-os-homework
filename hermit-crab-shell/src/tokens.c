#include "debug.h"

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

TOKEN *new_token_append()
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_APPEND;
    return t;
}

TOKEN *new_token_next()
{
    TOKEN *t;
    t = malloc(sizeof(TOKEN));
    t->type = TOKEN_TYPE_NEXT;
    return t;
}

// destructor of token list
// head is the pointer to the head pointer of token list
// *head will be NULL when function finished
void free_token_list(TOKEN_LIST_NODE **head)
{
    TOKEN_LIST_NODE *temp_node;

    while (*head != NULL)
    {
        temp_node = *head;
        *head = temp_node->next;
        // do not forget to free
        if (temp_node->tok->type == TOKEN_TYPE_STRING)
        {
            free(temp_node->tok->t_string.str);
        }
        free(temp_node);
    }
}
