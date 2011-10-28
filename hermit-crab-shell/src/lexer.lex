%top{

#include "debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "tokens.h"
#include "const.h"
#include "lexer.h"

int content_empty;
char content[STRING_MAX_LENGTH] = "";
int ioflag = 0;
TOKEN_LIST_NODE *head, *tail;


void add_token_node(TOKEN *t)
{
    if (head == NULL)
    {
        head = malloc(sizeof(TOKEN_LIST_NODE));        
        head->tok = t;
        head->next = NULL;
        tail = head;
    }
    else
    {
        tail->next = malloc(sizeof(TOKEN_LIST_NODE));
        tail = tail->next;
        tail->tok = t;
        tail->next = NULL;
    }
#ifdef DEBUG
    fprintf(stderr, "[lexer.c] new node added!\n");
    fprintf(stderr, "[lexer.c] head = %d, tail = %d\n", head, tail);
#endif
}

void content_start()
{
    if (content_empty)
    {
        strcpy(content, "");
        content_empty = 0;
    }
}

void content_end()
{
    if (!content_empty)
    {
        add_token_node(new_token_string(content));
        content_empty = 1;
    }
}

}

space  \n|\r|\t|\f|" "

%option noyywrap

%x DOUBLEQUOTE
%x SINGLEQUOTE

%%

<INITIAL>
{
    \"          { content_start(); BEGIN(DOUBLEQUOTE); }
    \'          { content_start(); BEGIN(SINGLEQUOTE); }
    \|          { content_end(); add_token_node(new_token_pipe()); }
    &           { content_end(); add_token_node(new_token_bg());; }
    \<          { content_end(); add_token_node(new_token_in()); }
    \>          { content_end(); add_token_node(new_token_out()); }
    \>\>        { content_end(); add_token_node(new_token_append()); }
    ;           { content_end(); add_token_node(new_token_next()); }
    {space}     { content_end(); }
    .           { content_start(); strcat(content, yytext); }
}

<DOUBLEQUOTE>
{
    \"          { BEGIN(INITIAL); }
    \\\"        { content_start(); strcat(content, "\""); }
    \\\\        { content_start(); strcat(content, "\\"); }
    .           { content_start(); strcat(content, yytext); }
}

<SINGLEQUOTE>
{
    \'          { BEGIN(INITIAL); }
    .           { content_start(); strcat(content, yytext); }
}

<<EOF>>         { content_end(); yyterminate(); }

%%

TOKEN_LIST_NODE *get_token_list(const char* s)
{
    head = tail = NULL;
    content_empty = 1;
    yy_scan_string(s);
    yylex();
    return head;
}

/*

// debug code
int main()
{
    TOKEN_LIST_NODE *h = get_token_list("test\"abc\"def\"t\" \"ttt\"");
    while (h != NULL)
    {
        switch (h->tok->type)
        {
        case TOKEN_TYPE_STRING:
            printf("%s %s\n", "STRING", h->tok->t_string.str);
            break;
        case TOKEN_TYPE_PIPE:
            printf("%s\n", "PIPE");
            break;
        case TOKEN_TYPE_BG:
            printf("%s\n", "BG");
            break;
        case TOKEN_TYPE_IN:
            printf("%s\n", "IN");
            break;
        case TOKEN_TYPE_OUT:
            printf("%s\n", "OUT");
            break;
        case TOKEN_TYPE_NEXT:
            printf("%s\n", "NEXT");
            break;
        }
        h = h->next;
    }
    printf("\n");
    return 0;
}
*/