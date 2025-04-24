#include "../inc/minishell.h"

char    *process_token(char *token, char **saveptr)
{
    char    *result;

    if (*token == '\'')
    {
        result = handle_single_quotes(saveptr);
        return (result);
    }
    if (*token == '"')
    {
        result = handle_double_quotes(saveptr);
        return (result);
    }
    if (strchr("|><", *token))
    {
        return (token);
    }
    return (token);
}

char *ft_strtok(char *str, const char *delim, char **saveptr)
{
    char *start;

    if (str != NULL)
        *saveptr = str;

    if (*saveptr == NULL)
        return (NULL);
    while (**saveptr && strchr(delim, **saveptr))
        (*saveptr)++;
    if (**saveptr == '\0')
        return (NULL);

    start = *saveptr;
    while (**saveptr && !strchr(delim, **saveptr))
        (*saveptr)++;
    if (**saveptr)
    {
        **saveptr = '\0';
        (*saveptr)++;
    }

    return (start);
}

int add_token(char ***tokens, unsigned int *position, size_t *bufsize, char *token)
{
    if (!token)
        return 0;
    token = trim_whitespace(token);
    if (!token)
        return 0;
    (*tokens)[(*position)++] = strdup(token);
    if (*position >= *bufsize)
    {
        *bufsize *= 2;
        *tokens = realloc(*tokens, *bufsize * sizeof(**tokens));
        if (!(*tokens))
            return (-1);
    }
    return (0);
}

char	**get_tokens(char *line)
{
	size_t			bufsize;
	char			*token;
	char 			**tokens;
	char            *saveptr;
	unsigned int 	position;

	if (!line || !*line) 
		return (NULL);	
	position = 0; //index dos tokens
	bufsize = 64; 
	tokens = ft_malloc(bufsize * sizeof (*tokens)); //array de chars
	if (!tokens)
		return (NULL);	
	token = ft_strtok(line, DELIM, &saveptr); //cada token separado
    while (token)
    {
        token = process_token(token, &saveptr);
		if (!token) // caso haja tokens invalidos
    		continue;
        if (add_token(&tokens, &position, &bufsize, token) == -1)
		{
			free_tokens(tokens);
			return (NULL);
		}
        token = ft_strtok(NULL, DELIM, &saveptr);
    }
	tokens[position] = NULL;
	return(tokens);
}
