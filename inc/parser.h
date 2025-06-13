/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:03:48 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 13:01:22 by renrodri         ###   ########.fr       */
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

typedef struct s_redir_data
{
        int     source_fd;
        t_redir_type    type;
        char    *fname;
        int     expand;
} t_redir_data;

/*
* @brief represents a redirection tied to a command
*/
typedef struct s_redirect
{
        int                     source_fd;
        t_redir_type            type;  
        char                    *filename;
        struct s_redirect       *next;
        int     	        expand_heredoc;

} t_redirect;

/*
* @brief represents a parsed shell command w args and redirections
*/
typedef struct s_command
{
        char                    *cmd;  
        char                    **args;      
        t_redirect              *redirs; 
        struct s_command        *next; 
        int                     is_pipe;
        int                     heredoc_pipe_read_fd;
        int                     pipe_fds[2];
        pid_t                   pid;
        int                     prev_pipe_read_fd;
}       t_command;

/* parser.c */
t_command	*parse_tokens(t_token *tokens, t_shell *shell);

/* parser_utils.c */
t_command	*init_command(void);
int			add_arg(t_command *cmd, char *arg);
int	add_redir(t_command *cmd, t_redir_data *data);
int			handle_cmd_or_arg(t_command *cmd, t_token *token);
t_command	*new_command(t_command *current);

/* parser_logic.c */
int			handle_word_token(t_command *cmd, t_token *tok, t_shell *shell);
// int			parse_redirection(t_command *cmd, t_token **token_ptr);
int			handle_special_token(t_command **cmd, t_token *tok);
t_token		*parse_redirection(t_command *cmd, t_token *token);

/* parser_syntax.c */
int			syntax_error(const char *token);
int			is_token_cmd(t_token *token);
int			is_token_redir(t_token *token);
void		expand_token_list(t_token *tokens, t_shell *shell);

/* free_commands.c */
void		free_commands(t_command *cmd);
void		free_redirs(t_redirect *redir);
void        print_commands(t_command *cmd);

 
#endif