/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:03:48 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 18:06:43 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
#include "tokens.h"

typedef struct s_shell t_shell;


typedef enum e_redir_type 
{
        REDIR_IN,
        REDIR_OUT, 
        REDIR_APPEND, 
        REDIR_HEREDOC 
}       t_redir_type;

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
        char *cmd;  
        char **args;      
        t_redirect *redirs; 
        struct s_command *next; 
        int is_pipe;
        int heredoc_pipe_read_fd;
        int pipe_fds[2];
        pid_t pid;
        int prev_pipe_read_fd;
}       t_command;


t_command   *new_command(t_command *current);
int         handle_special_tokens(t_command **current, t_token **tokens);
t_command   *parse_tokens(t_token *tokens, t_shell *shell);
int	        parse_redir(t_command *cmd, t_token **token_ptr);
t_command   *init_command(void);
int         add_arg(t_command *cmd, char *arg);
int         add_redir(t_command *cmd, t_redir_type type, char *filename);
int			handle_cmd_or_arg(t_command *cmd, t_token *token);
int			handle_redir(t_command *cmd, t_token *token);
void        print_commands(t_command *cmd);
void        free_commands(t_command *cmd);
void        free_redirs(t_redirect *redir);
int         syntax_error(const char *token);
int         is_token_cmd(t_token *token);
int         is_token_redir(t_token *token);
void        expand_token_list(t_token *tokens, t_shell *shell);

#endif