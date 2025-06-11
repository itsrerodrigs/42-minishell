/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:28:35 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/11 09:36:28 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

/* static char *ft_strjoin_free(char *s1, char *s2)
{
	char	*joined_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined_str = malloc(len1 + len2 + 1);
	if (!joined_str)
		return (NULL);
	ft_strlcpy(joined_str, s1, len1 + 1);
	ft_strlcat(joined_str, s2, len1 + len2 + 1);
	free(s1);
	return (joined_str);
}

static int ft_count_vars_to_keep(char **envp, const char *key)
{
	int count = 0;
	size_t key_len = ft_strlen(key);

	while (*envp)
	{
		if (!(ft_strncmp(*envp, key, key_len) == 0 && (*envp)[key_len] == '='))
			count++;
		envp++;
	}
	return count;
}

int	builtin_setenv(t_shell *shell, char **args)
{
	char	*key;
	char	*value;
	char	*new_var;
	char	**new_envp;
	int		i;

	if (!args[1] || !args[2])
	{
		ft_putstr_fd("setenv: Usage: setenv <key> <value>\n", STDERR_FILENO);
		return (1);
	}
	key = args[1];
	value = args[2];
	new_var = ft_strjoin(key, "=");
	if (!new_var)
		return (1);
	new_var = ft_strjoin(new_var, value);
	if (!new_var)
		return (1);
	new_envp = malloc(sizeof(char *) * (ft_count_vars_to_keep(shell->envp, key) + 2));
	if (!new_envp)
	{
		free(new_var);
		return (1);
	}
	i = 0;
	while (shell->envp[i])
	{
		if (!(ft_strncmp(shell->envp[i], key, ft_strlen(key)) == 0 && \
			shell->envp[i][ft_strlen(key)] == '='))
			new_envp[i] = ft_strdup(shell->envp[i]);
		else
			new_envp[i] = NULL;
		i++;
	}
	new_envp[i++] = new_var;
	new_envp[i] = NULL;
	free_envp(shell->envp);
	shell->envp = new_envp;
	return (0);
} */
