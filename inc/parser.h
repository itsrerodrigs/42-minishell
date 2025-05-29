/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:03:48 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/14 23:03:48 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
#include "tokens.h"

// assuming that t_token and t_token_type was defined in minishell.h
/**/
typedef enum e_redir_type {
    REDIR_IN, // <
    REDIR_OUT, // >
    REDIR_APPEND, // >>
    REDIR_HEREDOC // <<
} t_redir_type;

/*
* @brief represents a redirection tied to a command
*/
typedef struct s_redirect
{
    t_redir_type type;  /*type REDIR_IN, REDIR_OUT...*/
    char *filename; /*target filename or limiter for redirection*/
    struct s_redirect *next; /*pointer to the next redirection in the list*/
} t_redirect;

/*
* @brief represents a parsed shell command w args and redirections
*/
typedef struct s_command
{
    char *cmd;               /*main command like echo, ls...*/
    char **args;             /*NULL-terminated arr of args including cmd*/
    t_redirect *redirs;      /*linked list of redir associated w this command*/
    struct s_command *next;  /*pointer to the next command in sequence*/
    int is_pipe;             /*1 if connected via pipe, 0 if separated by semicolon */
} t_command;

/*
* @brief parses a linked list of tokens into a linked list of commands
* @param tokens pointer to the first token in the token list
* @return pointer to the head of the linked list of parsed commands
*/
t_command *new_command(t_command *current);
t_command *parse_tokens(t_token *tokens);
int	parse_redir(t_command *cmd, t_token **token_ptr);


/*
* @brief initializes and allocate memory for a new command structure
* @return pointer to the newly allocated command or NULL on failure
*/
t_command *init_command(void);
int         add_arg(t_command *cmd, char *arg);
int         add_redir(t_command *cmd, t_redir_type type, char *filename);
int			handle_cmd_or_arg(t_command *cmd, t_token *token);
int			handle_redir(t_command *cmd, t_token *token);

void print_commands(t_command *cmd);

#endif