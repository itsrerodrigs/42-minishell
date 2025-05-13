/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:07:01 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/12 22:10:46 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
** @brief: frees an array of token pointers
**@param: tokens - array of t_token pointers
*/
void	free_tokens(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/*
** @brif: creates a new oken from a buffer string (but)
** @param: buf - input string to store
** @return: pointer to the new token
*/
t_token *create_token(char *buf)
{
    t_token *input_token;

    if (!buf)
        return (NULL);

    input_token = ft_malloc(sizeof(t_token));
    if (!input_token)
    {
        free(buf);
        return (NULL);
    }
    input_token->value = ft_strdup(buf);
    input_token->type = TOKEN_VALUE;
    return (input_token);
}


/*
** @brief: initializes a dynamic array of tokens
** @param: bufsize - pointer to a size variable
**@return: pointer to the allocated array
*/
t_token **init_token_array(size_t *bufsize)
{
	t_token	**tokens;

	*bufsize = 64;
	tokens = ft_malloc(sizeof(t_token *) * (*bufsize + 1));
	if (!tokens)
	{
		p(RED "Debug: Error in init_token_array" RST);
		return (NULL);
	}
	tokens[*bufsize] = NULL;
	return (tokens);
}