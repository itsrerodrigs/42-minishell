/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/02 14:45:57 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_tokens(char *line)
{
	char			**tokens;
	char			*saveptr;
	size_t			bufsize;
	unsigned int	position;

	if (!line || !*line)
		return (NULL);
		
	tokens = initialize_token_array(&bufsize); /* cria um array vazio */
	if (!tokens)
		return (NULL);
		
	position = extract_tokens(line, &tokens, &bufsize, &saveptr);
	/* popula o array com os tokens */
	if (position == 0)
	{
		free_tokens(tokens);
		return (NULL);
	}
	tokens[position] = NULL;
	return (tokens);
}

static int	add_token(char ***tokens, unsigned int count, char *token)
{
	char	*processed_token;

	if (!token || *token == '\0')
		return (0);
	processed_token = ft_strdup(token);
	if (!processed_token)
		return (0);
	(*tokens)[count] = processed_token;
	return (1);
}

int	realloc_tokens(char ***tokens, size_t *bufsize)
{
	size_t	new_size;
	char	**new_tokens;

	new_size = *bufsize * 2;
	new_tokens = ft_realloc(*tokens, new_size * sizeof(char *));
	if (!new_tokens)
		return (0);
	*tokens = new_tokens;
	*bufsize = new_size;
	return (1);
}

unsigned int	extract_tokens(char *line, char ***tokens, size_t *bufsize,
		char **saveptr)
{
	char			*token;
	unsigned int	count;

	*saveptr = line;
	count = 0;
	if (!line || !tokens || !*tokens || !bufsize || !saveptr || *bufsize == 0)
		return (0);
		
	token = ft_strtok(line, DELIM, saveptr);
	if (!token)
        return (0);
	while (token)
	{				
		if (count >= *bufsize - 1 && !realloc_tokens(tokens, bufsize))
			return (0);
			
		if (*token != '\0')
		{
			if (!add_token(tokens, count++, token))
				return (0);			
		}
		token = ft_strtok(NULL, DELIM, saveptr);
	}
	(*tokens)[count] = NULL;
	return (count);
}

// char	*process_token(char *token, char **saveptr)
// {
// 	if (*token == '\'' || *token == '"')
// 		return (handle_quotes(saveptr, *token));
// 	if (strchr("|><", *token))
// 		return (token); /*mudar depois pra lidar com operators*/
// 	return (token);
// }