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

#include "tokens.h"
#include "parsing.h"
#include "builtins.h"
#include "debug.h"

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


/*------------------------Prototypes------------------------------------*/
/*input*/
char        *display_prompt(void);
char        *read_input(void);
t_token     *process_input(void);
void         setup_signal_handling(void);


/*builtins*/
int         ft_exit(char **args);


/*signals*/
void        sigint_handler(int signum);

/*memory*/
void        *ft_malloc(size_t size);
void	    *ft_realloc(void *ptr, size_t size);



#endif