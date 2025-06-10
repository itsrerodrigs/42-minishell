#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h> 
#include <sys/ioctl.h>
#include <limits.h>
#include <stdbool.h> 
#include "libft/libft.h"
#include "builtins.h"
#include "tokens.h"
#include "parser.h"
#include "executor.h"
#include "sig.h"
#include <fcntl.h>

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

/*memory*/
void        *ft_malloc(size_t size);
void	    *ft_realloc(void *ptr, size_t size);
void    free_str_array(char **array);


#endif