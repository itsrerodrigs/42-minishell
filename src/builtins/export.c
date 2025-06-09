/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:56:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 20:26:18 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 * @brief Sorts the environment variables alphabetically using bubble sort.
 * This remains static to this file.
 * @param envp The environment array to sort.
 */
static void sort_env(char **envp)
{
    int     i;
    int     j;
    char    *temp;
    int     len;

    len = 0;
    while (envp[len])
        len++;

    i = 0;
    while (i < len - 1)
    {
        j = i + 1;
        while (j < len)
        {
            if (ft_strcmp(envp[i], envp[j]) > 0)
            {
                temp = envp[i];
                envp[i] = envp[j];
                envp[j] = temp;
            }
            j++;
        }
        i++;
    }
}

/*
 * @brief Handles the reallocation and addition of a new environment entry.
 * This function is static to this file, called only by add_or_update_env.
 * @param envp_ptr Pointer to the shell's environment array.
 * @param var The variable string to add (e.g., "KEY=VALUE" or "KEY").
 * @param i The index where the new variable should be added.
 * @return 1 on successful addition, 0 on memory allocation failure.
 */
static int s_add_new_env_entry(char ***envp_ptr, const char *var, int i)
{
    char **new_envp_array;

    new_envp_array = (char **)ft_realloc(*envp_ptr, sizeof(char *) * (i + 2));
    if (!new_envp_array)
    {
        perror("minishell: realloc failed in export");
        return (0); 
    }
    *envp_ptr = new_envp_array; 
    (*envp_ptr)[i] = ft_strdup(var);

	if (!(*envp_ptr)[i])
    {
		if (errno == 0 || errno == EINTR)
				errno = ENOMEM;
        perror("minishell: strdup failed in export");
        return (0); 
    }
    (*envp_ptr)[i + 1] = NULL; 
    return (1);
}

/*
 * @brief Adds or updates an environment variable in the shell's environment.
 * @param envp_ptr Pointer to the shell's environment array (char ***).
 * @param var The variable string (e.g., "KEY=VALUE" or "KEY").
 * @return 0 on success, 1 on failure (e.g., memory allocation, invalid name).
 */
int add_or_update_env(char ***envp_ptr, const char *var)
{
    int     i;
    char    *equals_pos;
    size_t  key_len;
    int     var_has_value;

    i = 0;
    equals_pos = ft_strchr(var, '=');
    var_has_value = (equals_pos != NULL);
    if (var_has_value)
        key_len = equals_pos - var;
    else
        key_len = ft_strlen(var);    
    if (!is_valid_env_name(var, key_len))
        return (1);
    while ((*envp_ptr)[i])
    {
        if (try_update_existing_var(envp_ptr, var, key_len, var_has_value))
            return (0); 
        i++;
    }

    if (!s_add_new_env_entry(envp_ptr, var, i))
        return (1); 
    return (0); 
}

/*
 * @brief Built-in 'export' command.
 * @param shell The shell context.
 * @param args The arguments array.
 * @return 0 on success, 1 on error.
 */
int builtin_export(t_shell *shell, char **args)
{
    int i;
    int return_status;

	return_status = 0;
    if (!shell || !shell->envp)
        return (1);

    if (!args[1]) 
    {
        sort_env(shell->envp);
        i = 0;
        while (shell->envp[i])
        {
            ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
            i++;
        }
        return (0);
    }
    else 
    {
        i = 1;
        while (args[i])
        {
            if (add_or_update_env(&shell->envp, args[i]) != 0)
                return_status = 1;
            i++;
        }
    }
    return (return_status);
}
