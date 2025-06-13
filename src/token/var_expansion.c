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
#include "tokens.h"

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

static void	append_expanded_var(t_expansion_state *state)
{
	char	*value;
	char	*temp;
	char	*old_expanded;

	(state->i)++;
	value = extract_variable(state->input, &state->i, state->shell->envp);
	if (!value)
		return ;
	old_expanded = state->expanded;
	state->new_size += ft_strlen(value);
	temp = ft_realloc(state->expanded, state->new_size + 1);
	if (!temp)
	{
		free(old_expanded);
		free(value);
		state->expanded = NULL;
		return ;
	}
	state->expanded = temp;
	ft_strlcat(state->expanded, value, state->new_size + 1);
	free(value);
}

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

static void	process_expansion_segment(t_expansion_state *state)
{
	if (state->input[state->i] == '\\' && state->input[state->i + 1] == '$')
	{
		state->expanded = append_char(state->expanded, '$', &state->new_size);
		state->i += 2;
	}
	else if (is_var_start(state->input, state->i))
		append_expanded_var(state);
	else
	{
		state->expanded = append_char(state->expanded,
				state->input[state->i], &state->new_size);
		(state->i)++;
	}
}

char	*expand_variables(const char *input, char **envp, int exit_status)
{
	t_expansion_state	state;
	t_shell				dummy_shell;

	if (!input)
		return (NULL);
	dummy_shell.envp = envp;
	dummy_shell.exit_status = exit_status;
	state.input = input;
	state.new_size = 0;
	state.i = 0;
	state.shell = &dummy_shell;
	state.expanded = ft_strdup("");
	if (!state.expanded)
		return (NULL);
	while (state.input[state.i])
	{
		process_expansion_segment(&state);
		if (!state.expanded)
			return (NULL);
	}
	return (state.expanded);
}
