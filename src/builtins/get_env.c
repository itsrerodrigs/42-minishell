/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:47:37 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/07 13:47:37 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief returns the value of a given environment variable
* @params envp is an array of environment strings in the KEY=VALUE format
* key is the environment variable name to search for
@note returns NULL if the variable is not found
*/

/* pode dar problema com fork, execvp e execve!!! */
char    *get_env_value(char **envp, const char *key)
{
    int i;
    size_t key_len;

    key_len = ft_strlen(key);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
            return (&envp[i][key_len + 1]);
        i++;
    }
    return (NULL);
}