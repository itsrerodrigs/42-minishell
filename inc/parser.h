/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:03:48 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 19:57:33 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "tokens.h"

typedef struct s_shell	t_shell;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir_data
{
	t_redir_type	type;
	int				source_fd;
	int				expand;
	char			*fname;
}	t_redir_data;

/*
* @brief represents a redirection tied to a command
*/
typedef struct s_redirect
{
	struct s_redirect	*next;
	int					source_fd;
	int					expand_heredoc;
	char				*filename;
	t_redir_type		type;
}	t_redirect;

/*
* @brief represents a parsed shell command w args and redirections
*/
typedef struct s_command
{
	struct s_command	*next;
	char				*cmd;
	char				**args;
	t_redirect			*redirs;
	int					is_pipe;
	int					heredoc_pipe_read_fd;
	int					pipe_fds[2];
	pid_t				pid;
	int					prev_pipe_read_fd;
}	t_command;

/* parser.c */
t_command		*parse_tokens(t_token *tokens, t_shell *shell);
int				is_all_digits(const char *str);

/* parser handlers */
t_token			*s_handle_redirection_token(t_command *current_cmd,
					t_token *tok);
t_token			*s_parse_loop_iteration(t_command **current_cmd_ptr,
					t_token *tok, t_shell *shell, t_command *cmd_list);

/* parser_utils.c */
int				add_arg(t_command *cmd, char *arg);
int				add_redir(t_command *cmd, t_redir_data *data);
int				handle_cmd_or_arg(t_command *cmd, t_token *token);
t_command		*new_command(t_command *current);
t_command		*init_command(void);
t_redir_type	get_redir_type(t_token *token);

/* parser_logic.c */
int				handle_word_token(t_command *cmd, t_token *tok, t_shell *shell);
int				handle_special_token(t_command **cmd, t_token *tok);
t_token			*parse_redirection(t_command *cmd, t_token *token);

/* parser_syntax.c */
int				syntax_error(const char *token);
int				is_token_cmd(t_token *token);
int				is_token_redir(t_token *token);
void			expand_token_list(t_token *tokens, t_shell *shell);

/* free_commands.c */
void			free_commands(t_command *cmd);
void			free_redirs(t_redirect *redir);
void			print_commands(t_command *cmd);

#endif
