/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:59:25 by marieli           #+#    #+#             */
/*   Updated: 2025/06/12 11:59:35 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

/**
 * @brief Expands a tilde (~) at the beginning of a string to the HOME
 * directory path. It handles `~` and `~/...`.
 *
 * @param original_value The string to expand.
 * @param shell The shell context to get the HOME variable.
 * @return A new, allocated string with the tilde expanded, or a copy of the
 * original string if no tilde expansion was needed. Returns NULL on error.
 */
char	*expand_tilde(const char *original_value, t_shell *shell)
{
	char	*home_dir;
	char	*expanded_path;

	if (!original_value || original_value[0] != '~')
		return (ft_strdup(original_value));
	home_dir = get_env_value(shell->envp, "HOME");
	if (!home_dir)
		return (ft_strdup(original_value));
	if (original_value[1] == '\0')
		return (ft_strdup(home_dir));
	if (original_value[1] == '/')
	{
		expanded_path = ft_strjoin(ft_strdup(home_dir),
				(char *)&original_value[1]);
		return (expanded_path);
	}
	return (ft_strdup(original_value));
}