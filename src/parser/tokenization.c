#include "../inc/minishell.h"

char    **get_tokens(char *line)
{
    char            **tokens;
    char            *saveptr;
    size_t          bufsize;
    unsigned int    position;

    if (!line || !*line)
        return (NULL);

    tokens = initialize_token_array(&bufsize);
    if (!tokens)
        return (NULL);

    position = extract_tokens(line, tokens, bufsize, &saveptr);
    if (position == 0)
    {
        free_tokens(tokens);
        return (NULL);
    }
    tokens[position] = NULL;
    free_tokens(tokens);
    return (tokens);
}


char	*process_token(char *token, char **saveptr)
{
	char	*result;

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

unsigned int	extract_tokens(char *line, char **tokens, size_t bufsize,
    char **saveptr)
{
unsigned int	position;
char			*token;

position = 0;
token = ft_strtok(line, DELIM, saveptr);
while (token != NULL)
{
    token = process_token(token, saveptr);
    if (token == NULL)
    {
        continue ;
    }
    if (add_token(&tokens, &position, &bufsize, token) == -1)
    {
        free_tokens(tokens);
        return (0);
    }
    token = ft_strtok(NULL, DELIM, saveptr);
}
return (position);
}

char	*ft_strtok(char *str, const char *delim, char **saveptr)
{
	char	*start;

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

int	add_token(char ***tokens, unsigned int *position, size_t *bufsize,
		char *token)
{
	if (!token)
		return (0);
	token = trim_whitespace(token);
	if (!token)
		return (0);
	(*tokens)[(*position)++] = ft_strdup(token);
	if (*position >= *bufsize)
	{
		*bufsize *= 2;
		*tokens = ft_realloc(*tokens, *bufsize * sizeof(**tokens));
		if (!(*tokens))
			return (-1);
	}
	return (0);
}

