<<<<<<< HEAD:src/utils/memory_utils.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:35 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/09 15:14:09 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

/*
** @brief: Allocates memory of size 'size' and returns a pointer to it.
** @param: size  size of memory to allocate.
** @return:  pointer to the allocated memory.
*/
void *ft_malloc(size_t size)
{
    void *ptr;
    
    if (size == 0)
        return(NULL);
    ptr = malloc(size);
    if (!ptr)
        perror(RED "ft_malloc: allocation failed" RST);
    return(ptr);
}

/*
** @brief: reallocater memory with error checking
** @paam: ptr - pointer to the previoulsy allocated memory
** @param: size - size of memory to allocate, in bytes
** @return: pointer to reallocated memory
*/
void	*ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

    if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
	new_ptr =  realloc(ptr, size);
	if (!new_ptr)
		perror(RED "ft_realloc: reallocation failed" RST);
	return(new_ptr);
}

=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:35 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/01 19:30:21 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

void *ft_malloc(size_t size)
{
    void *ptr;
    
    if (size == 0)
        return(NULL);
    ptr = malloc(size);
    if (!ptr)
    {
        perror(RED "Malloc failed\n" RST);
        exit (EXIT_FAILURE);
    }
    return(ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

    if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
	new_ptr =  realloc(ptr, size);
	if (!new_ptr && size != 0)
	{
		perror(RED "Realloc failed\n" RST);
		exit(EXIT_FAILURE);
	}
	return(new_ptr);
}

void    *ft_getcwd(char *buf, size_t size)
{
    if (NULL == getcwd(buf, size))
    {
		perror (RED "Getcwd FAILED" RST);
		buf[0] = '\0';
	}
    return(buf);
}

char    **initialize_token_array(size_t *bufsize)
{
    char    **tokens;

    *bufsize = 64;
    tokens = ft_malloc(*bufsize * sizeof(*tokens));
    if (!tokens)
    {
        p(RED "Error in initialize_token_array" RST);
        return (NULL);
    }
    return (tokens);
}

void free_tokens(char **tokens)
{
    unsigned int i;
    
    if (!tokens) 
    return;

    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        tokens[i] = NULL;
        i++;
    }
    free(tokens);
    tokens = NULL;
}
>>>>>>> builtins-test:src/utils/memory.c
