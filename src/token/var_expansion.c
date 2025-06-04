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

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parser.h"

/*
 ** @brief: Resizes the expanded string buffer based on the inserted value.
 ** @param: expanded - current expanded string, 
 **          new_size - pointer to buffer size, 
 **          value - string to add.
 ** @return: pointer to resized expanded string.
 */
static char *resize_expanded(char *expanded, size_t *new_size, const char *value)
{
    char *temp;
    *new_size += ft_strlen(value);
    temp = ft_realloc(expanded, *new_size + 1);
    if (!temp)
    {
        free(expanded);
        return (NULL);
    }
    return (temp);
}

/*
 ** @brief: Expands an encountered variable.
 ** @param: input - source string
 **		    index_ptr - pointer to index, 
 **		    expanded - current expanded string,
 **         new_size - pointer to current allocated size.
 ** @return: pointer to updated expanded string.
 */
// static char *need_expansion(const char *input, size_t *index_ptr, char *expanded, size_t *new_size, char **envp)
// {
//     char *value;

//     (*index_ptr)++;
//     value = extract_variable(input, index_ptr, envp);
//     if (!value)
//         value = ft_strdup("");
//     expanded = resize_expanded(expanded, new_size, value);
//     if (!expanded)
//     {
//         free(value);
//         return (NULL);
//     }
//     ft_strlcat(expanded, value, *new_size + 1);
//     free(value);
//     return (expanded);
// }

/*
 ** @brief: Appends a regular (non-variable) character to the expanded string.
 ** @param: input - source string, 
 **         index_ptr - current index pointer, 
 **         expanded - the built string,
 **         new_size - pointer to current size.
 ** @return: pointer to updated expanded string.
 */
static char *regular_char(const char *input, size_t *index_ptr, char *expanded, size_t *new_size)
{
    char *temp;
    
    temp = ft_realloc(expanded, *new_size + 2);
    if (!temp)
    {
        free(expanded);
        return (NULL);
    }
    expanded = temp;
    expanded[*new_size] = input[*index_ptr];
    expanded[*new_size + 1] = '\0';
    (*new_size)++;
    (*index_ptr)++;
    return (expanded);
}

/*
 ** @brief: Expands all environment variables in the input string.
 ** @param: input - the source string
 ** @return: new dynamically allocated string with variables expanded.
 */
// char *expand_variables(const char *input, char **envp)
// {
//     char    *expanded;
//     size_t  new_size;
//     size_t  index_ptr;

//     if (!input)
//         return (NULL);
//     new_size = 0;
//     index_ptr = 0;
//     expanded = malloc(ft_strlen(input) + 1);
//     if (!expanded)
//         return (NULL);
//     expanded[0] = '\0';
//     while (input[index_ptr])
//     {
//         if (input[index_ptr] == '$' && input[index_ptr + 1] != '\0')
//             expanded = need_expansion(input, &index_ptr, expanded, &new_size, envp);
//         else
//             expanded = regular_char(input, &index_ptr, expanded, &new_size);
//         if (!expanded)
//         {
//             free(expanded);
//             return (NULL);  
//         }
//     }
//     return (expanded);
// }

// void expand_token_list(t_token *tokens, t_shell *shell)
// {
//     while (tokens)
//     {
//         if (tokens->type == TOKEN_SINGLE_QUOTED)
//         {
//             tokens = tokens->next;
//             continue;
//         }
//         char *expanded = expand_variables(tokens->value, shell->envp);
//         if (expanded)
//         {
//             free(tokens->value);
//             tokens->value = expanded;
//         }
//         tokens = tokens->next;
//     }
// }

static char *need_expansion(const char *input, size_t *index_ptr, char *expanded, size_t *new_size, char **envp, int exit_status) // Added exit_status
{
    char *value;

    (*index_ptr)++;
    value = extract_variable(input, index_ptr, envp, exit_status);
    expanded = resize_expanded(expanded, new_size, value);
    if (!expanded)
    {
        free(value);
        return (NULL);
    }
    ft_strlcat(expanded, value, *new_size + 1);
    free(value);
    return (expanded);
}

char *expand_variables(const char *input, char **envp, int exit_status)
{
    char    *expanded;
    size_t  new_size;
    size_t  index_ptr;

    if (!input)
        return (NULL);
    new_size = 0;
    index_ptr = 0;
    expanded = malloc(ft_strlen(input) + 1);
    if (!expanded)
        return (NULL);
    expanded[0] = '\0';
    while (input[index_ptr])
    {
        // Correctly handle '$' at the end of string or followed by non-variable char
        if (input[index_ptr] == '$' && input[index_ptr + 1] != '\0' &&
            (ft_isalpha(input[index_ptr + 1]) || input[index_ptr + 1] == '_' ||
             input[index_ptr + 1] == '?' || input[index_ptr + 1] == '$' ||
             input[index_ptr + 1] == '{')) // Check for valid start of var name
        {
            expanded = need_expansion(input, &index_ptr, expanded, &new_size, envp, exit_status); // Pass exit_status
        }
        else if (input[index_ptr] == '$' && input[index_ptr + 1] == '\0') // Case: "echo $"
        {
            expanded = regular_char(input, &index_ptr, expanded, &new_size); // Treat as regular char '$'
        }
        else if (input[index_ptr] == '$' && ft_isspace(input[index_ptr + 1])) // Case: "echo $ "
        {
            expanded = regular_char(input, &index_ptr, expanded, &new_size); // Treat as regular char '$'
        }
        else
            expanded = regular_char(input, &index_ptr, expanded, &new_size);
        
        if (!expanded)
        {
            // free(expanded); // Already freed in regular_char/need_expansion if NULL is returned
            return (NULL);  
        }
    }
    return (expanded);
}

void expand_token_list(t_token *tokens, t_shell *shell)
{
    while (tokens)
    {
        if (tokens->type == TOKEN_SINGLE_QUOTED)
        {
            tokens = tokens->next;
            continue;
        }
        // Pass shell->exit_status to expand_variables
        char *expanded = expand_variables(tokens->value, shell->envp, shell->exit_status);
        if (expanded) // expanded will never be NULL if allocation succeeds, but check anyway
        {
            free(tokens->value);
            tokens->value = expanded;
        }
        tokens = tokens->next;
    }
}