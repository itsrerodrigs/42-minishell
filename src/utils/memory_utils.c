/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:35 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parser.h"

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
