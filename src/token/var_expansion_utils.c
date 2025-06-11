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
#include "parser.h"

static int s_is_var_char(char c)
{
    return (ft_isalnum(c) || c == '_'); 
}

static void extract_var_name(const char *input, size_t *index_ptr, char *var_name)
{
    size_t var_length;

    var_length = 0;
    if (input[*index_ptr] == '?' || input[*index_ptr] == '$')
    {
        var_name[var_length] = input[*index_ptr];
        var_length++;
        (*index_ptr)++;
    }
    else
    {
        while (input[*index_ptr] && s_is_var_char(input[*index_ptr]))
        {
            var_name[var_length] = input[*index_ptr];
            var_length++;
            (*index_ptr)++;
        }
    }
    var_name[var_length] = '\0';
}
char *extract_variable(const char *input, size_t *index_ptr, char **envp, int exit_status)
{
    char var_name[BUFFER_SIZE];
    char *value;
    pid_t pid_val;

    value = NULL;
    if (input[*index_ptr] == '{')
    {
        (*index_ptr)++;
        extract_var_name(input, index_ptr, var_name);
        if (input[*index_ptr] == '}')
            (*index_ptr)++;
    }
    else
        extract_var_name(input, index_ptr, var_name);
    if (ft_strcmp(var_name, "?") == 0) 
        return (ft_itoa(exit_status)); 
    if (ft_strcmp(var_name, "$") == 0) 
    {
        pid_val = getpid();
        return (ft_itoa(pid_val));
    }
    if (var_name[0] == '\0')
        return (ft_strdup("")); 
    value = get_env_value(envp, var_name); 
    if (!value)
        return (ft_strdup("")); 
    return (ft_strdup(value));
}
