#ifndef TOKENIZATION_H
#define TOKENIZATION_H

#include "minishell.h"

typedef enum e_token_type
{
    TOKEN_WORD,         // Regular command or argument (e.g., "ls", "echo") 
    TOKEN_SINGLE_QUOTED, // Single-quoted string (e.g., 'hello world') 
    TOKEN_DOUBLE_QUOTED, // Double-quoted string (e.g., "hello world") 
    TOKEN_PIPE,          // Pipe symbol "|" 
    TOKEN_REDIR_OUT,     // Output redirection ">" 
    TOKEN_REDIR_IN,      // Input redirection "<" 
    TOKEN_APPEND,        // Append redirection ">>" 
    TOKEN_HEREDOC,       // Here-document "<<" 
    TOKEN_EOF,           // End of file (useful for parsing) 
    TOKEN_SEMICOLON      // Command separator ";" 
} t_token_type;


typedef struct s_token {
    char            *value;
    t_token_type    type;
    int             index;
    struct s_token  *next;
} t_token;


/*token*/
void        free_tokens(t_token *head);
t_token     *create_token(char *buf, t_token_type type);
t_token     *extract_tokens(char **saveptr);
t_token_type    get_token_type(char *token_str);
t_token     *get_tokens(char *input);
char        *ft_strtok(char *str, const char *delim, char **saveptr);

/*quotes*/
t_token     *handle_quotes(char **saveptr, char quote_char);


#endif