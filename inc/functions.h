
# ifndef FUNCTIONS_H
# define FUNCTIONS_H

// #include <stddef.h> // For size_t
// #include <unistd.h> // For pid_t

// /* -----input handling--------- */
// char	*display_prompt(void);
// char 	*read_input(void);
// t_token *create_token(char *buf);

// /* -------Tokens------ */
// char    		*ft_strtok(char *str, const char *delim, char **saveptr);
// t_token			**get_tokens(t_token *input);
// unsigned int	extract_tokens(char *input, t_token ***tokens, size_t *bufsize, char **saveptr);
// char   			**initialize_token_array(size_t *bufsize);

// /* ---------quotes--------- */
// char *handle_quotes(char **saveptr, char quote);

// /* ------Exec-------- */
// // void	ft_exec(char **args);
// void    sigint_handler(int signum);

// /* ----------Built-in---------- */
// // int     ft_env(char **args);
// // int     ft_exit(char **args);

// /* ------------Memory------------ */
// void    *ft_malloc(size_t size);
// void	*ft_realloc(void *ptr, size_t size);
// void 	free_tokens(t_token **tokens);

// /* ------------Loop----------------- */
// // pid_t   ft_wait(int *status);
// // void    ft_execvp(const char *file, char *const argv[]);
// // pid_t   ft_fork(void);

// /* -------------------Utils-------------- */
// void    *ft_getcwd(char *buf, size_t size);
// void    printbanner(void);

#endif