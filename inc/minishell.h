#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "libft/libft.h"

#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST		"\033[0m"

#define p(...) printf(__VA_ARGS__)
#define DELIM " \t\n\v\f\r"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024   
#endif

#define INITIAL_TOKENS_CAPACITY 16

typedef enum e_token_type
{
    TOKEN_VALUE,         /* Regular command or argument (e.g., "ls", "echo")  */
    TOKEN_SINGLE_QUOTED, /* Single-quoted string (e.g., 'hello world')  */
    TOKEN_DOUBLE_QUOTED, /* Double-quoted string (e.g., "hello world")  */
    TOKEN_PIPE,          /* Pipe symbol "|"  */
    TOKEN_REDIR_OUT,     /* Output redirection ">"  */
    TOKEN_REDIR_IN,      /* Input redirection "<"  */
    TOKEN_APPEND,        /* Append redirection ">>"  */
    TOKEN_HEREDOC,       /* Here-document "<<"  */
    TOKEN_EOF,           /* End of file (useful for parsing)  */
    TOKEN_SEMICOLON      /* Command separator ";"  */
} t_token_type;


typedef struct s_token 
{
    char *value;
    t_token_type type;
    // int redir_fd;
    // int syntax_error; 
} t_token;


/* exec_builtin */
typedef struct s_cmd {
    char **args; 
    int argc; /* numero de args passados */
} t_cmd;

typedef struct s_shell {
    t_cmd *current_cmd; 
    char **envp; /* cópia do ambiente do sistema que manipula export e unset */
    int exit_status; /* ultimo estatus de saída do shell */
} t_shell;

/*------------------------Prototypes------------------------------------*/
/*input*/
char        *display_prompt(void);
t_token     *read_input(void);

/*token*/
void	    free_tokens(t_token **tokens);
t_token     *create_token(char *buf);
t_token     **init_token_array(size_t *bufsize);
int         realloc_tokens(t_token ***tokens_ptr, size_t *bufsize);
t_token     **get_tokens(t_token *input);
char    	*ft_strtok(char *str, const char *delim, char **saveptr);

/*execução dos comandos*/
void ft_exec(t_shell *shell);

/*builtins*/
int ft_exit(char **args);

/*variable expansion*/
char *extract_variable(const char *input, size_t *index_ptr);
char *expand_variables(const char *input);

/*quotes*/
t_token *handle_quotes(char **saveptr, char quote_char);

/*signals*/
void sigint_handler(int signum);

/*memory*/
void        *ft_malloc(size_t size);
void	    *ft_realloc(void *ptr, size_t size);


#endif