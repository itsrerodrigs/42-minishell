/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:31:23 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/12 22:11:01 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** @brief: doubles the size of the token array
** @param: tokens - a pointer to the array pointer
** @param: bufsize - a pointer to the size variable
** @param: saveptr - tokenizer state pointer for ft_strtok
** @return: 1 on success, 0 on failure
*/
// Updated realloc_tokens: tokens_ptr is a triple pointer.
int realloc_tokens(t_token ***tokens_ptr, size_t *bufsize)
{
    if (!tokens_ptr || !*tokens_ptr || !bufsize)
        return 0;

    size_t new_size = *bufsize * 2;
    t_token **new_tokens = (t_token **)ft_realloc(*tokens_ptr, new_size * sizeof(t_token *));
    if (!new_tokens)
        return 0;

    *tokens_ptr = new_tokens;
    *bufsize = new_size;
    return 1;
}


/*
** @brief: extract tokens from the input string nd stores them in an array
** @param: input - input string
** @param: tokens - pointer to token array
** @param: bufsize -current size of the token array
** @param: saveptr - tokenizer state pointer for ft_strtok
*/
static unsigned int extract_tokens(t_token *input, t_token ***tokens, size_t *bufsize, char **saveptr)
{
	char 		*token; /* token to be extracted */
	unsigned int count; /* count of tokens added */

	count = 0;
	token = NULL;
	if (!input || !tokens || !*tokens || !bufsize || !saveptr || *bufsize == 0)
		return (0);

	*saveptr = input->value;
	token = ft_strtok(input->value, DELIM, saveptr);
	if(!token)
	{
		(*tokens)[0] = NULL;
		return (0);
	}
		
	while (token)
	{
		if(count >= *bufsize -1)
		{
			*bufsize *= 2;
			if(!realloc_tokens(tokens, bufsize))
				return (0);
		}
		(*tokens)[count++] = create_token(token);
		token = ft_strtok(NULL, DELIM, saveptr);
	}
	(*tokens)[count] = NULL;
	return (count);
}

/*
** Cbrief: split the input string into an array of tokens (calls extract_tokens)
** @param: input - input string
** @param: tokens - pointer to token array
** @param: bufsize -current size of the token array
** @param: saveptr - tokenizer state pointer for ft_strtok
*/
t_token **get_tokens(t_token *input)
{
	t_token 		**tokens;
	size_t			bufsize;
	unsigned int	count;
	char			*saveptr;

	if (!input || !input->value)
		return (NULL);
	bufsize = INITIAL_TOKENS_CAPACITY;
	tokens = ft_malloc(bufsize * sizeof(t_token *));
	if (!tokens)
		return (NULL);
	saveptr = input->value;
	count = extract_tokens(input, &tokens, &bufsize, &saveptr);
	if (count == 0)
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}