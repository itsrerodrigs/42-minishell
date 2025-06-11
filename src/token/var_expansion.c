/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:46 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends a regular (non-variable) character to the expanded string.
 */
static char	*append_char(char *expanded, char c, size_t *new_size)
{
	char	*temp;

	temp = ft_realloc(expanded, *new_size + 2);
	if (!temp)
	{
		free(expanded);
		return (NULL);
	}
	expanded = temp;
	expanded[*new_size] = c;
	expanded[*new_size + 1] = '\0';
	(*new_size)++;
	return (expanded);
}

/**
 * @brief Expands an encountered variable and appends its value.
 */
static char	*append_expanded_var(char *expanded, size_t *n_size, const char *in,
	size_t *idx, t_shell *shell)
{
	char	*value;
	char	*temp;
	char	*old_expanded;

	(*idx)++;
	value = extract_variable(in, idx, shell->envp, shell->exit_status);
	if (!value)
		return (expanded);
	old_expanded = expanded;
	*n_size += ft_strlen(value);
	temp = ft_realloc(expanded, *n_size + 1);
	if (!temp)
	{
		free(old_expanded);
		free(value);
		return (NULL);
	}
	expanded = temp;
	ft_strlcat(expanded, value, *n_size + 1);
	free(value);
	return (expanded);
}

/**
 * @brief Checks if the current character signals the start of a variable.
 */
static int	is_var_start(const char *input, size_t index)
{
	char	next_char;

	if (input[index] != '$')
		return (0);
	next_char = input[index + 1];
	if (ft_isalpha(next_char) || next_char == '_' || next_char == '?'
		|| next_char == '$' || next_char == '{')
		return (1);
	return (0);
}

/**
 * @brief Expands all variables in a string (e.g., $VAR or ${VAR}).
 */
char	*expand_variables(const char *input, char **envp, int exit_status)
{
	char	*expanded;
	size_t	new_size;
	size_t	i;
	t_shell	dummy_shell;

	if (!input)
		return (NULL);
	new_size = 0;
	i = 0;
	dummy_shell.envp = envp;
	dummy_shell.exit_status = exit_status;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (input[i])
	{
		if (is_var_start(input, i))
			expanded = append_expanded_var(expanded, &new_size, input, &i, &dummy_shell);
		else
			expanded = append_char(expanded, input[i++], &new_size);
		if (!expanded)
			return (NULL);
	}
	return (expanded);
}

/**
 * @brief Iterates through a token list and expands variables in WORD tokens.
 */
void	expand_token_list(t_token *tokens, t_shell *shell)
{
	char	*expanded_value;

	while (tokens)
	{
		if (tokens->type != TOKEN_SINGLE_QUOTED)
		{
			expanded_value = expand_variables(tokens->value, shell->envp,
					shell->exit_status);
			if (expanded_value)
			{
				free(tokens->value);
				tokens->value = expanded_value;
			}
		}
		tokens = tokens->next;
	}
}
