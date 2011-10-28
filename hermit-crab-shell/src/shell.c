/*
 * Shell Main Process
 *
 *  Including some major functions for the whole shell.
 *  The main() function is here.
 */

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "const.h"
#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include "prompt.h"


// Variables
char *single_line,
     *prompt,
     line[STRING_MAX_LENGTH];
TOKEN_LIST_NODE *token_list_head;
PARSE_STATUS p;
pid_t *pid_list; // PIDs to wait
int pid_list_len; // length of pid_list

// Initialize all vairables of the shell, and other init operations
void shell_initialize(void)
{
    // clear the pointers
    single_line = NULL;
    prompt = NULL;
    token_list_head = NULL;
    pid_list = NULL;

    pid_list_len = 0;

    // using history
    using_history();

    // set umask
    umask(0);
}

int main(int argc, char **argv)
{
    int i;

    // initialize the shell
    shell_initialize();

    while (1)
    {
        // get last directory of current working directory
        prompt = get_prompt();

        // read command
        strcpy(line, "");
        single_line = readline(prompt);
        while (strlen(single_line) > 0 &&
                 single_line[strlen(single_line) - 1] == '\\')
                 // if need to read more
                 // TODO(sqybi@126.com): not completed, e.g.,
                 //   [test "ab] also need more text
        {
            strcat(line, single_line);
            free(single_line);
            single_line = readline("> ");
            line[strlen(line) - 1] = '\0';
        }
        strcat(line, single_line);

        // add to history
        // TODO(sqybi@126.com): maybe some bug here
        free(single_line);
        single_line = calloc(sizeof(char), strlen(line) + 1);
        strcpy(single_line, line);
        add_history(single_line);
        // do NOT free single_line!

#ifdef DEBUG
        fprintf(stderr, "[shell.c] line = %s\n", line);
#endif

        // get tokens
        token_list_head = get_token_list(line);

        // parse grammar tree
        // will fork processes here
        p = parse(token_list_head);

        if (p != PARSE_STATUS_NORMAL)
        {
            printf("[hcsh] Syntax error code %d.\n", p);
        }

        // wait processes
#ifdef DEBUG
        fprintf(stderr, "[shell.c] pid_list_len = %d\n", pid_list_len);
#endif
        for (i = 0; i != pid_list_len; ++i)
        {
            waitpid(pid_list[i], NULL, 0);
        }

        // do some free operation
        free_token_list(token_list_head);
        if (pid_list_len != 0)
        {
            free(pid_list);
            pid_list = NULL;
            pid_list_len = 0;
        }
        free(prompt);
        free(single_line);
    }
    return 0;
}
