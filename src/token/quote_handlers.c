/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:24 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/07 16:43:47 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

static char *extract_variable(const char *input, size_t *index_ptr)
{
    static char var_name[BUFFER_SIZE];
    size_t  var_length;
    char    *value;

    var_length = 0;
    while(input[*index_ptr] && (input[*index_ptr] != ' ') && input[*index_ptr] != '"')
    {
        var_name[var_length++] = input[*index_ptr];
        (*index_ptr)++;
    }
    var_name[var_length] = '\0';
    
    value = getenv(var_name);
    if(value == NULL)
        return (" ");
    return(value);
}

static char *need_expansion(const char *input, size_t *index_ptr, char *expanded, size_t *new_size)
{
    char *value;

    (*index_ptr)++;
    value = extract_variable(input, index_ptr);
    *new_size += ft_strlen(value);
    expanded = ft_realloc(expanded, *new_size + 1);
    ft_strlcat(expanded, value, *new_size + 1);
    
    return(expanded);   
}

static char *regular_char(const char *input, size_t *index_ptr, char *expanded, size_t *new_size)
{
    (*new_size)++;
    expanded = ft_realloc(expanded, *new_size + 1);
    ft_strlcat(expanded, &input[*index_ptr], *new_size + 1);
    (*index_ptr)++;

    return (expanded);
}

char    *expand_variables(const char *input)
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
        return(NULL);
    expanded[0] = '\0';
    while(input[index_ptr])
    {
        if (input[index_ptr] == '$' && input[index_ptr + 1] != '\0')
        {
            expanded = need_expansion(input, &index_ptr, expanded, &new_size);
            if (!expanded)
                return (NULL);
        }
        else
        {
            expanded = regular_char(input, &index_ptr, expanded, &new_size);
            if (!expanded)
                return (NULL);  
        }

    }
    return(expanded);
}


char *handle_quotes(char **saveptr, char quote_char)
{
    char    *start; 
    char    *end;
    char    *expanded;

    if (!saveptr || !*saveptr || **saveptr != quote_char)
        return NULL;

    start = ++(*saveptr);
    end = start;
    while (*end && *end != quote_char)
        end++;
    if (*end == '\0')
    {
        printf("Error: Unmatched quote!\n");
        *saveptr = NULL;
        return (NULL);
    }
    *end = '\0';
    *saveptr = end + 1;
    
    if (start && *start) // Ensure `start` is valid and not empty
    {
        expanded = expand_variables(start);
        if (!expanded) // Handle memory allocation failure in `expand_variables`
        {
            printf("Error: Memory allocation failed during variable expansion.\n");
            return (NULL);
        }
        return (expanded);
    }
    return (NULL); 
}

