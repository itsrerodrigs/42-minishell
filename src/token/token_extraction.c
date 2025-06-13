/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:02:00 by marieli           #+#    #+#             */
/*   Updated: 2025/06/11 11:02:00 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

t_token	*create_token(char *buf, t_token_type type)
{
	t_token	*new_token;

	if (!buf)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(buf);
		return (NULL);
	}
	new_token->value = ft_strdup(buf);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static t_token	*extract_tokens(char **saveptr, t_shell *shell)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;

	head = NULL;
	current = NULL;
	new_token = ft_get_next_token(NULL, DELIM, saveptr, shell);
	while (new_token)
	{
		if (!head)
			head = new_token;
		else
			current->next = new_token;
		current = new_token;
		new_token = ft_get_next_token(NULL, DELIM, saveptr, shell);
	}
	return (head);
}

t_token	*get_tokens(char *input, t_shell *shell)
{
	char	*saveptr;

	if (!input)
		return (NULL);
	saveptr = input;
	return (extract_tokens(&saveptr, shell));
}
