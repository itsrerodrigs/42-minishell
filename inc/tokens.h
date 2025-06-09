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
        int fd;
        struct s_token  *next;
} t_token;


/*token*/
char        *read_input(void);
void        free_tokens(t_token *head);
t_token     *create_token(char *buf, t_token_type type);
t_token     *get_tokens(char *input, t_shell *shell);
t_token_type get_token_type(char *token_str);
t_token     *ft_get_next_token(char *str, const char *delim, char **saveptr, t_shell *shell);
char        *extract_next_token(char **saveptr, const char *delim);
t_token *create_token_with_fd(char *value, t_token_type type, int fd_val);


/*quotes*/
t_token *handle_quotes(char **saveptr, char quote_char, t_shell *shell);
char *extract_quoted(char **saveptr, char quote_char);

/*variable expansion*/
char *extract_variable(const char *input, size_t *index_ptr, char **envp, int exit_status);
char *expand_variables(const char *input, char **envp, int exit_status);

#endif