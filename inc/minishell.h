#ifndef SHELL_H
# define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sysexits.h>
#include <ctype.h> //trocar por libft depois
#include <signal.h>
#include <errno.h>
#include "libft/libft.h"

#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST		"\033[0m"

#define p(...) printf(__VA_ARGS__)
#define DELIM " \t\n\v\f\r"

#define CELL_Jr 0

typedef struct s_bultin
{
        const char  *builtin_name;
        int (*foo)(char **);
}       t_builtin;


//-----input handling---------
void    display_prompt(void);
char	**split_line(char *line);
char 	*read_input(void);
void    sigint_handler(int signum);


//------Exec--------
void	ft_exec(char **args);
void    ft_launch(char **args);

//------Built-in----------
int     ft_env(char **args);
int     ft_exit(char **args);

//-----Memory------
void    *ft_malloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);

//------Loop-------
pid_t   ft_wait(int *status);
void    ft_execvp(const char *file, char *const argv[]);
pid_t   ft_fork(void);

//-------Utils-------
void    *ft_getcwd(char *buf, size_t size);
void    printbanner(void);


#endif