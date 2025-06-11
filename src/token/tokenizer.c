/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:01:13 by marieli           #+#    #+#             */
/*   Updated: 2025/06/11 11:01:13 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"


/**
 * @brief Advances the save pointer past any delimiter characters.
 */
static void	skip_delim(char **saveptr, const char *delim)
{
	while (**saveptr && ft_strchr(delim, **saveptr))
		(*saveptr)++;
}

/**
 * @brief Gets a word or quoted token, handling special quote syntax.
 */
static t_token	*get_word_or_quote_token(const char *d, char **s, t_shell *sh)
{
	char quote_char;
	char *token_val;
	t_token *new_token;

	quote_char = **s;
	if (quote_char == '\'' || quote_char == '"')
	{
		new_token = handle_quotes(s, quote_char, sh);
		return (new_token);
	}
	token_val = extract_next_token(s, d);
	if (!token_val)
		return (NULL);
	new_token = create_token_with_fd(token_val, TOKEN_WORD, -1);
	return (new_token);
}

/**
 * @brief Retrieves the next complete token from the input string.
 */
t_token	*ft_get_next_token(char *str, const char *delim, char **saveptr,
		t_shell *shell)
{
	t_token *new_token;
	const char *ws_delim;

	ws_delim = " \t\n";
	if (!saveptr || !delim)
		return (NULL);
	if (str)
		*saveptr = str;
	skip_delim(saveptr, ws_delim);
	if (**saveptr == '\0')
		return (NULL);
	new_token = extract_operator_token(saveptr);
	if (new_token)
		return (new_token);
	new_token = get_word_or_quote_token(delim, saveptr, shell);
	return (new_token);
}
