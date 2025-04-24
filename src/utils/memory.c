/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:35 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/24 18:28:36 by mmariano         ###   ########.fr       */
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

	new_ptr =  realloc(ptr, size);
	if (!new_ptr && size != 0)
	{
		perror(RED "Realloc failed\n" RST);
		exit(EXIT_FAILURE);
	}
    free(new_ptr);
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
        return (NULL);

    return (tokens);
}
