#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h> // waitpid, fork e exceve
#include <sys/ioctl.h>
#include <limits.h> // PATH_MAX
#include "libft/libft.h"
#include "builtins.h"
#include "tokens.h"
#include "parser.h"
#include "executor.h"
#include "sig.h"

#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST		"\033[0m"

#define p(...) printf(__VA_ARGS__)
#define DELIM " \t\n|<>&;()"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024   
#endif

#define INITIAL_TOKENS_CAPACITY 16

extern volatile sig_atomic_t g_child_running;

/*typedef enum e_token_type
{
    TOKEN_VALUE,         // Regular command or argument (e.g., "ls", "echo") 
    TOKEN_SINGLE_QUOTED, // Single-quoted string (e.g., 'hello world') 
    TOKEN_DOUBLE_QUOTED, // Double-quoted string (e.g., "hello world") 
    TOKEN_PIPE,          // Pipe symbol "|"  
    TOKEN_REDIR_OUT,     // Output redirection ">" 
    TOKEN_REDIR_IN,      // Input redirection "<"  
    TOKEN_APPEND,        // Append redirection ">>"  add redir_append
    TOKEN_HEREDOC,       // Here-document "<<" add redir_heredoc 
    TOKEN_EOF,           // End of file (useful for parsing) 
    TOKEN_SEMICOLON      // Command separator ";"  
} t_token_type;*/

/* exec_builtin  EXCLUIR ESSE BLOCO!
typedef struct s_cmd {
    char **args; 
    int argc;  // numero de args passados
} t_cmd;

typedef struct s_shell { EXCLUIR ESSE BLOCO
    t_cmd *current_cmd; 
    char **envp; // cópia do ambiente do sistema que manipula export e unset
    int exit_status; // ultimo estatus de saída do shell
} t_shell;*/

/*------------------------Prototypes------------------------------------*/
/*input*/
// char        *display_prompt(void);
char     *read_input(void);


/*memory*/
void        *ft_malloc(size_t size);
void	    *ft_realloc(void *ptr, size_t size);

void ft_exit(t_shell *shell);
void fill_shell_struct(t_shell *shell, char **args);
char **simple_split(char *input);

#endif