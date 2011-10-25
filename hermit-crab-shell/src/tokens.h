#ifndef __TOKENS_H__
#define __TOKENS_H__

// type of tokens
typedef enum token_type
{
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_PIPE,
    TOKEN_TYPE_BG,
    TOKEN_TYPE_IN,
    TOKEN_TYPE_OUT,
    TOKEN_TYPE_NEXT
} TOKEN_TYPE;

// definition of tokens
typedef struct token_string
{
    TOKEN_TYPE type;
    char *str;
} TOKEN_STRING;

typedef struct token_pipe
{
    TOKEN_TYPE type;
} TOKEN_PIPE;

typedef struct token_bg
{
    TOKEN_TYPE type;
} TOKEN_BG;

typedef struct token_in
{
    TOKEN_TYPE type;
} TOKEN_IN;

typedef struct token_out
{
    TOKEN_TYPE type;
} TOKEN_OUT;

typedef struct token_next
{
    TOKEN_TYPE type;
} TOKEN_NEXT;

// union for token
typedef union token
{
    TOKEN_TYPE type;
    TOKEN_STRING t_string;
    TOKEN_PIPE t_pipe;
    TOKEN_BG t_bg;
    TOKEN_IN t_in;
    TOKEN_OUT t_out;
    TOKEN_NEXT t_next;
} TOKEN;

// functions to create token
TOKEN *new_token_string(const char *s);
TOKEN *new_token_pipe();
TOKEN *new_token_bg();
TOKEN *new_token_in();
TOKEN *new_token_out();
TOKEN *new_token_next();

// list of tokens
typedef struct token_list_node
{
    TOKEN *tok;
    struct token_list_node *next;
} TOKEN_LIST_NODE;

#endif
