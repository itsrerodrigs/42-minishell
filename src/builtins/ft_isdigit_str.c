/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int ft_isdigit_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:23:01 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/11 22:23:01 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isdigit_str(const char *str)
{
    while (*str) {
        if (!ft_isdigit(*str)) {
            return (0);
        }
        str++;
    }
    return (1);
}