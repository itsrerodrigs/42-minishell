/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:59:25 by marieli           #+#    #+#             */
/*   Updated: 2025/06/13 15:47:58 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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
