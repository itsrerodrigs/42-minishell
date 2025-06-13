/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:28:25 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static void	extract_var_name(const char *input, size_t *idx, char *var_name)
{
	size_t	var_len;

	var_len = 0;
	if (input[*idx] == '?' || input[*idx] == '$')
	{
		var_name[var_len] = input[*idx];
		var_len++;
		(*idx)++;
	}
	else
	{
		while (input[*idx] && is_var_char(input[*idx]))
		{
			var_name[var_len] = input[*idx];
			var_len++;
			(*idx)++;
		}
	}
	var_name[var_len] = '\0';
}

static char	*handle_special_var(const char *var_name)
{
	pid_t	pid_val;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_strdup(EXIT_STATUS_MARKER));
	if (ft_strcmp(var_name, "$") == 0)
	{
		pid_val = getpid();
		return (ft_itoa(pid_val));
	}
	return (NULL);
}

char	*extract_variable(const char *input, size_t *idx, char **envp)
{
	char	var_name[BUFFER_SIZE];
	char	*value;

	if (input[*idx] == '{')
	{
		(*idx)++;
		extract_var_name(input, idx, var_name);
		if (input[*idx] == '}')
			(*idx)++;
	}
	else
		extract_var_name(input, idx, var_name);
	value = handle_special_var(var_name);
	if (value)
		return (value);
	if (var_name[0] == '\0')
		return (ft_strdup("$"));
	value = get_env_value(envp, var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

void	expand_token_list(t_token *tokens, t_shell *shell)
{
	char	*temp_val;
	char	*final_val;

	while (tokens)
	{
		if (tokens->type != TOKEN_SINGLE_QUOTED)
		{
			temp_val = expand_tilde(tokens->value, shell);
			if (!temp_val)
			{
				tokens = tokens->next;
				continue ;
			}
			final_val = expand_variables(temp_val, shell->envp,
					shell->exit_status);
			free(temp_val);
			if (final_val)
			{
				free(tokens->value);
				tokens->value = final_val;
			}
		}
		tokens = tokens->next;
	}
}
