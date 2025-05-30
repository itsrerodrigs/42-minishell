/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parser.h"

/*
** @brief: skips the whitespace characters in the input string
** @param: input - input string
** @return: pointer to the first non-whitespace character
*/
static void skip_delim(char **saveptr, const char *delim)
{
	while (**saveptr && ft_strchr(delim, **saveptr))
		(*saveptr)++;
}

/*
 ** @brief: Handles quoted strings inside ft_strtok.
 ** @param saveptr: Pointer to the tokenizer state.
 ** @return: Extracted quoted string or NULL if an error occurs.
 */
static char *handle_token_quotes(char **saveptr, t_shell *shell)
{
    t_token *quoted_token;
    char quote_char;

    if (!saveptr || !*saveptr)
        return (NULL);

    quote_char = **saveptr;
    if (quote_char != '\'' && quote_char != '"')
        return (NULL);
    quoted_token = handle_quotes(saveptr, quote_char, shell);
    if (quoted_token)
        return quoted_token->value;

    return (NULL);
}


/*
 ** @brief: Extracts the next token from the input string.
 ** @param saveptr: Pointer to the tokenizer state.
 ** 		delim: Delimiter characters.
 ** @return: Extracted token string.
 */
static char *extract_next_token(char **saveptr, const char *delim)
{
    char *start;

    if (!saveptr || !*saveptr || !delim)
        return (NULL);

    start = *saveptr;
    while (**saveptr && !ft_strchr(delim, **saveptr))
        (*saveptr)++;

    if (**saveptr)
    {
        **saveptr = '\0';
        (*saveptr)++;
    }
    return (start);
}
/*
 ** @brief: Custom tokenizer that handles quotes and delimiters.
 ** @param str: Input string (or NULL to continue tokenizing).
 ** 		delim: Delimiter characters.
 ** 		saveptr: Pointer to track progress across calls.
 ** @return: Pointer to the next token, or NULL if no token remains.
 */
char *ft_strtok(char *str, const char *delim, char **saveptr, t_shell *shell)
{
    char *token;

    if (!saveptr || !delim)
        return (NULL);
    if (str)
        *saveptr = str;
    skip_delim(saveptr, delim); 
    if (**saveptr == '\0')
        return (NULL);
    if (**saveptr == '\'' || **saveptr == '"')
    {
        token = handle_token_quotes(saveptr, shell);
        if (token)
            return (token);
    }
    return (extract_next_token(saveptr, delim));
}
