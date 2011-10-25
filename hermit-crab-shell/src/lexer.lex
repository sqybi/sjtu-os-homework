%top{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "tokens.h"
#include "const.h"

int string_finished;
char content[STRING_MAX_LENGTH] = "";
int ioflag = 0;
TOKEN_LIST_NODE *head, *tail;

void add_token_node(TOKEN *t)
{
    if (head == NULL)
    {
        head = malloc(sizeof(TOKEN_LIST_NODE));
        tail = head;
    }
    else
    {
    	tail->next = malloc(sizeof(TOKEN_LIST_NODE));
    	tail = tail->next;
    }
}

}

space  \n|\r|\t|\f|" "

%option noyywrap

%x STRINGMODE

%%

<INITIAL>
{
    \"          { string_finished = 0; strcpy(content, ""); BEGIN(STRINGMODE); }
    \|          { add_token_node(new_token_pipe()); }
    &           { add_token_node(new_token_bg());; }
    \>          { add_token_node(new_token_in()); }
    \<          { add_token_node(new_token_out()); }
    ;           { add_token_node(new_token_next()); }
    {space}     { }
    [^" "]*     { add_token_node(new_token_string(yytext)); }
}

<STRINGMODE>
{
    {space}     { if (string_finished) { add_token_node(new_token_string(content)); BEGIN(INITIAL); } else strcat(content, yytext); }
    \"          { string_finished = 1 - string_finished; }
    .           { strcat(content, yytext); }
}

%%

TOKEN_LIST_NODE *get_token_list(const char* s)
{
    head = tail = NULL;
    char *ts = malloc(strlen(s) + 2);
    strcpy(ts, s);
    strcat(ts, " ");
    yy_scan_string(ts);
    yylex();
    return head;
}
