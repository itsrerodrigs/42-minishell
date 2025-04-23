#include "../include/minishell.h""

char	**ft_split_line(char *line)
{
	unsigned int 	position;
	size_t			bufsize;
	char			*token;
	char 			**tokens;

	if (!line || !*line) 
		return (NULL);
	
	position = 0;
	bufsize = BUFSIZ;
	tokens = ft_malloc(bufsize * sizeof (*tokens));
	token = strtok(line, DELIM);

	while (token != NULL)
	{
		tokens[position] = strdup(token); //trocar pelo da libft
		position++;
		if (position >= bufsize)
		{
			bufsize *= 2;
			tokens = ft_realloc(tokens, bufsize *sizeof (*tokens));
		}
		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return(tokens);
}
