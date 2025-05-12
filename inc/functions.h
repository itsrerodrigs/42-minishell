
# ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include <stddef.h> // For size_t
#include <unistd.h> // For pid_t

typedef struct s_shell t_shell;

//-----input handling---------
void    display_prompt(void);
char 	*read_input(void);
void    sigint_handler(int signum);
char    *trim_whitespace(char *str);

//-------Tokens------
char    *ft_strtok(char *str, const char *delim, char **saveptr);
char	**get_tokens(char *line);
//char    *process_token(char *token, char **saveptr);
unsigned int	extract_tokens(char *line, char ***tokens, size_t *bufsize, char **saveptr);
void    free_tokens(char **tokens);
char    **initialize_token_array(size_t *bufsize);

//-----quotes---------
char *handle_quotes(char **saveptr, char quote);


//------Exec--------
void	ft_exec(char **args);
void    ft_launch(char **args);

//------Built-in----------
int     ft_env(char **args);
int     ft_exit(char **args);
char    *get_env_value(char **envp, const char *key);
int builtin_cd(t_shell *shell, char **args);
int builtin_echo(t_shell *shell, char **args);
int builtin_env(t_shell *shell, char **args);
int builtin_exit(t_shell *shell, char **args);
int builtin_unset(t_shell *shell, char **args);
int builtin_pwd(t_shell *shell, char **args);

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