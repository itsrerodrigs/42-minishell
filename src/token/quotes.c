/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:15:45 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parsing.h"

/*
**	@brief: extracts a quotes substring from the input
** @param: 	saveptr - state pointer, 
** 			quote_char - type of quote
** @return: pointer to extracted quoted string
*/
char *extract_quoted(char **saveptr, char quote_char)
{
	char *start;
	char *end;

	start = ++(*saveptr);
	end = start;
	while (*end)
	{
		if (*end == '\\' && (*(end +1) == quote_char))
		{
			end += 2;
			continue;
		}
		if (*end == quote_char)
			break;
		end++;
	}
	if (*end == '\0')
	{
		p("Error: Unmatched quote\n");
		*saveptr = NULL;
		return (NULL);
	}
	*end = '\0';
	*saveptr = end + 1;
	return(start);
}


/*
** @brief:  call extract quotes and applies variable expansion for double quotes
** @param: saveptr - pointer to tokenizer state, 
**		quote_char - quoting character
** @return: new token constructed from the quoted input
*/
t_token *handle_quotes(char **saveptr, char quote_char)
{
	char *start;
	char *expanded;
	
	if (!saveptr || !*saveptr || **saveptr != quote_char)
		return (NULL);
	start = extract_quoted(saveptr, quote_char);
	if (!start)
		return (NULL);
	if(quote_char == '"')
	{
		expanded = expand_variables(start);
		if(!expanded)
		{
			p("Error: Memory allocation failed during variable expansion.\n");
			return (NULL);
		}
		return (create_token(expanded, TOKEN_WORD));
	}
	return(create_token(start,TOKEN_WORD));
}
