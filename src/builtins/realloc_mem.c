/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:27:01 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 13:35:02 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief reallocates memory for a pointer with a new size
* @return a poiter to the new allocated mem block or NULL if the alloc fails
* @note if the new size is zero the function will free the mem and return NULL
*/
// char   **realloc_mem(char **ptr, size_t new_size)
// {
//     char    **new_ptr;

//     new_ptr = realloc(ptr, new_size);
//     if (!new_ptr)
//         perror("Error reallocating memory");
//     return (new_ptr);
// }