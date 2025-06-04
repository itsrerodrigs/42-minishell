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

// /*
// ** @brief: extract the variable name from the input string(skips $, {, etc)
// ** @param: input - source string
// ** @param: index_ptr - current index pointer
// ** @param:  var_name - to store the token/name
// */
// static void extract_var_name(const char *input, size_t *index_ptr, char *var_name)
// {
// 	size_t var_length;
	
// 	var_length = 0;
//     while (input[*index_ptr] && input[*index_ptr] != ' ' &&
// 		input[*index_ptr] != '"' && input[*index_ptr] != '}')
//  	{
// 		var_name[var_length] = input[*index_ptr];
// 		var_length++;
// 		(*index_ptr)++;
//  	}
//  	var_name[var_length] = '\0';	
// }

// /*
// ** @brief: extracts the varable and retrieves the environment value
// ** @param: input - source string
// ** @param: index_ptr - current index pointer
// ** @return: pointer to environment value
// */
// char *extract_variable(const char *input, size_t *index_ptr, char **envp)
// {
// 	char var_name[BUFFER_SIZE];
// 	char *value;
// 	int i;

// 	value = NULL;
// 	if(input[*index_ptr] == '{')
// 	{
// 		(index_ptr)++;
// 		extract_var_name(input, index_ptr, var_name);
// 		if (input[*index_ptr] == '}')
// 			(*index_ptr)++;
// 	}
// 	else
// 		extract_var_name(input, index_ptr, var_name);
// 	if(!envp)
// 		return NULL;
// 	i = 0;
// 	while (envp[i])
// 	{
//     if (strncmp(envp[i], var_name, strlen(var_name)) == 0 &&
//         envp[i][strlen(var_name)] == '=')
//     {
//         value = ft_strdup(envp[i] + strlen(var_name) + 1);
//         break;
//     }
//     i++;
// 	}
// 	if (!value)
// 	{
// 		p(RED "Debug:Variable not found: %s\n" RST, (const char *)var_name);
// 		return (NULL);
// 	}
// 	return (value);
// }


// Helper to check if a character is valid for a variable name (alphanumeric or underscore)
static int s_is_var_char(char c)
{
    return (ft_isalnum(c) || c == '_'); // Assuming ft_isalnum is available
}

static void extract_var_name(const char *input, size_t *index_ptr, char *var_name)
{
    size_t var_length;

    var_length = 0;
    // Special handling for $? and $$
    if (input[*index_ptr] == '?' || input[*index_ptr] == '$')
    {
        var_name[var_length] = input[*index_ptr];
        var_length++;
        (*index_ptr)++;
    }
    // Standard variable name characters: alphanumeric or underscore
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
    pid_t pid_val; // For $$

    value = NULL;
    // Handle braced parameters first
    if (input[*index_ptr] == '{')
    {
        (*index_ptr)++;
        extract_var_name(input, index_ptr, var_name);
        if (input[*index_ptr] == '}')
            (*index_ptr)++;
    }
    else
        extract_var_name(input, index_ptr, var_name);

    // Handle special shell variables: $? and $$
    if (ft_strcmp(var_name, "?") == 0) // Assuming ft_strcmp is available
        return (ft_itoa(exit_status)); // Assuming ft_itoa converts int to string
    if (ft_strcmp(var_name, "$") == 0) // For $$
    {
        pid_val = getpid();
        return (ft_itoa(pid_val));
    }
    // Handle $ followed by non-variable char or end of string (e.g., "$ " or "$")
    if (var_name[0] == '\0')
        return (ft_strdup("")); // Bash prints nothing for $ followed by space, or $ at end of string

    // Lookup in environment
    value = get_env_value(envp, var_name); // Your existing helper

    if (!value)
        return (ft_strdup("")); // Return empty string for unset variables
    return (ft_strdup(value)); // get_env_value returns a pointer into envp, so strdup it.
}


