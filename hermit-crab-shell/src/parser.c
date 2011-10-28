#include "debug.h"

#ifdef DEBUG
#include <stdio.h>
#endif
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "const.h"
#include "tokens.h"
#include "command.h"
#include "parser.h"
#include "dir.h"

extern pid_t *pid_list;
extern int pid_list_len;

// check if token is a connector
int is_connector(TOKEN *t)
{
    return t->type == TOKEN_TYPE_PIPE ||
           t->type == TOKEN_TYPE_NEXT ||
           t->type == TOKEN_TYPE_BG;
}

// parse the whole token list
// when error occurs, return value won't be 0
PARSE_STATUS parse(TOKEN_LIST_NODE *head)
{
    return parse_connector(head, NULL);
}

// parse | and ;
// parse tokens from head (include) to tail (*exclude*)
PARSE_STATUS parse_connector(TOKEN_LIST_NODE *head, TOKEN_LIST_NODE *tail)
{
    TOKEN_LIST_NODE *cur;
    PARSE_STATUS p;

    // parse has finished!
    if (head == tail)
        return PARSE_STATUS_NORMAL;


    // check until connector occurs
    cur = head;
    while (cur->next != tail && !is_connector(cur->tok))
    {
        cur = cur->next;
    }

    // check if a pipe operator (|) at the end
    if (cur->tok->type == TOKEN_TYPE_PIPE &&
        cur->next == tail)
    {
        return PARSE_STATUS_ILLEGAL_CONNECTOR;
    }

#ifdef DEBUG
    fprintf(stderr, "[parser.c] parse command %d %d\n", head, cur->next);
#endif
    p = parse_command(head, cur->next);
    if (p != PARSE_STATUS_NORMAL)
        return p;

#ifdef DEBUG
    fprintf(stderr, "[parser.c] parse connector %d %d\n", cur->next, tail);
#endif
    p = parse_connector(cur->next, tail);
    if (p != PARSE_STATUS_NORMAL)
            return p;

    return PARSE_STATUS_NORMAL;
}

// parse command to run
// parse tokens from head (include) to tail (*exclude*)
PARSE_STATUS parse_command(TOKEN_LIST_NODE *head, TOKEN_LIST_NODE *tail)
{
    COMMAND_INFO info;
    char *temp, *pwd;
    int i;

    init_command_info(&info);

    while (head != tail)
    {
        switch (head->tok->type)
        {
        case TOKEN_TYPE_IN:
            // move to next token
            head = head->next;

            // must be a string after the < operator
            if (head->tok->type != TOKEN_TYPE_STRING)
            {
                free_command_info(info);
                return PARSE_STATUS_FILENAME_EXPECTED;
            }

            // check if file not exist
            pwd = calloc(sizeof(char *), STRING_MAX_LENGTH);
            getcwd(pwd, STRING_MAX_LENGTH);
            temp = connect_dir(pwd, head->tok->t_string.str);
            free(pwd);
            if (access(temp, 0) == -1)
            {
                free_command_info(info);
                return PARSE_STATUS_FILE_NOT_EXIST;
            }
            free(temp);

            info.input_file = head->tok->t_string.str;

            break;

        case TOKEN_TYPE_OUT:
            // move to next token
            head = head->next;

            // must be a string after the < operator
            if (head->tok->type != TOKEN_TYPE_STRING)
            {
                free_command_info(info);
                return PARSE_STATUS_FILENAME_EXPECTED;
            }

            // if file not exist, create it, or clear it
            close(open(head->tok->t_string.str, O_WRONLY | O_CREAT, 0644));

            info.output_file = head->tok->t_string.str;
            info.append_mode = 0;

            break;

        case TOKEN_TYPE_APPEND:
            // move to next token
            head = head->next;

            // must be a string after the < operator
            if (head->tok->type != TOKEN_TYPE_STRING)
            {
                free_command_info(info);
                return PARSE_STATUS_FILENAME_EXPECTED;
            }

            // if file not exist, create it, or do nothing
            close(open(head->tok->t_string.str, O_WRONLY | O_CREAT | O_APPEND, 0644));

            info.output_file = head->tok->t_string.str;
            info.append_mode = 1;

            break;

        case TOKEN_TYPE_STRING:
            // the first string is always command
            if (info.command == NULL)
            {
                info.command = head->tok->t_string.str;
            }
            // add this string to parameters
            ++info.parameters_len;
            info.parameters = realloc(info.parameters, sizeof(char *) * info.parameters_len);
            info.parameters[info.parameters_len - 1] = head->tok->t_string.str;

            break;

        case TOKEN_TYPE_BG:
            info.background_mode = 1;

            break;

        case TOKEN_TYPE_PIPE:
            info.output_to_pipe = 1;

            break;

        case TOKEN_TYPE_NEXT:
            info.wait_processes = 1;

        // other tokens
        default:
            // do nothing
            break;
        }
        head = head->next;
    }

    // If command equals to NULL... Hey, you are kidding.
    // No commands here, what should I run instead?
    if (info.command == NULL)
    {
        free_command_info(info);
        return PARSE_STATUS_COMMAND_EXPECTED;
    }
    else
    {
#ifdef DEBUG
        fprintf(stderr, "[parser.c] will run command %s!\n", info.command);
#endif
        run_command(&info);
        if (info.wait_processes)
        {
            for (i = 0; i != pid_list_len; ++i)
            {
                waitpid(pid_list[i]);
            }
            free(pid_list);
            pid_list = NULL;
            pid_list_len = 0;
        }
        free_command_info(info);
        return PARSE_STATUS_NORMAL;
    }
}
