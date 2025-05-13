/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:28:25 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/12 22:11:54 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

/*
** @brief: extract the variable name from the input string(skips $, {, etc)
** @param: input - source string
** @param: index_ptr - current index pointer
** @param:  var_name - to store the token/name
*/
static void extract_var_name(const char *input, size_t *index_ptr, char *var_name)
{
	size_t var_length;
	
	var_length = 0;
    while (input[*index_ptr] && input[*index_ptr] != ' ' &&
		input[*index_ptr] != '"' && input[*index_ptr] != '}')
 	{
		var_name[var_length] = input[*index_ptr];
		var_length++;
		(*index_ptr)++;
 	}
 	var_name[var_length] = '\0';	
}

/*
** @brief: extracts the varable and retrieves the environment value
** @param: input - source string
** @param: index_ptr - current index pointer
** @return: pointer to environment value
*/
char *extract_variable(const char *input, size_t *index_ptr)
{
	char var_name[BUFFER_SIZE];
	char *value;

	if(input[*index_ptr] == '{')
	{
		(index_ptr)++;
		extract_var_name(input, index_ptr, var_name);
		if (input[*index_ptr] == '}')
			(*index_ptr)++;
	}
	else
		extract_var_name(input, index_ptr, var_name);
	value = getenv((const char *)var_name);
	if (!value)
	{
		p(RED "Debug:Variable not found: %s\n" RST, (const char *)var_name);
		return (NULL);
	}
	return (value);
}