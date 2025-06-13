/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/13 16:30:05 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 16:30:05 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "tokens.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		perror(RED "ft_malloc: allocation failed" RST);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_malloc(size));
	new_ptr = realloc(ptr, size);
	if (!new_ptr)
		perror(RED "ft_realloc: reallocation failed" RST);
	return (new_ptr);
}
