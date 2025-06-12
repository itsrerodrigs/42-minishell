/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:55:42 by marieli           #+#    #+#             */
/*   Updated: 2025/06/12 10:55:42 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
#define TOKENS_H

#include "minishell.h"

typedef struct s_shell t_shell;

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_SINGLE_QUOTED,
    TOKEN_DOUBLE_QUOTED,
    TOKEN_PIPE,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_IN,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_EOF,
    TOKEN_SEMICOLON
} t_token_type;


typedef struct s_token 
{
        char            *value;
        t_token_type    type;
        int             index;
        int             fd;
        struct s_token  *next;
} t_token;


/* input.c */
void	s_process_loop(t_shell *shell);
void	init_shell_job_control(t_shell *shell);
void	init_shell_struct(t_shell *shell);
char	*read_input(t_shell *shell);

/* tokenizer.c */
t_token		*ft_get_next_token(char *str, const char *d, char **s, t_shell *sh);

/* tokenizer_logic.c */
char		*extract_next_token(char **saveptr, const char *delim);
t_token		*extract_operator_token(char **saveptr);

/* tokenizer_utils.c */
int			append_to_builder(char **token_builder_ptr, char *segment);
int			process_quoted_segment(char **builder, char **pos);
int			is_token_operator(char c);
int			process_unquoted_segment(char **b, char **p, const char *d);

/* quotes.c */
t_token		*handle_quotes(char **saveptr, char quote_char, t_shell *shell);
char		*extract_quoted(char **saveptr, char quote_char);

/* token_extraction.c */
void		free_tokens(t_token *head);
t_token		*create_token(char *buf, t_token_type type);
t_token		*get_tokens(char *input, t_shell *shell);

/* token_utils.c */
t_token		*create_token_with_fd(char *value, t_token_type type, int fd_val);

/* quotes.c */
t_token		*handle_quotes(char **saveptr, char quote_char, t_shell *shell);
char		*extract_quoted(char **saveptr, char quote_char);

/* var_expansion.c */
char        *extract_variable(const char *input, size_t *index_ptr, char **envp, int exit_status);
char		*expand_variables(const char *input, char **envp, int exit_status);
void		expand_token_list(t_token *tokens, t_shell *shell);

#endif