/* REMOVER ARQUIVO
#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

typedef struct s_cmd 
{
    char            **args;      // arguments (command name + params)
    int             argc;   // number of arguments added
    // In future: list of redirections (e.g., a linked list of redirection structs)
    struct s_cmd    *next;       // for a pipeline: pointer to next command
} t_cmd;

t_cmd *create_command(void);


variable expansion
char        *extract_variable(const char *input, size_t *index_ptr);
char        *expand_variables(const char *input);

#endif*/