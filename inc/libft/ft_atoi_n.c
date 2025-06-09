/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:52:33 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 18:53:03 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_atoi_n(const char *str, size_t n)
{
    int res = 0;
    size_t i = 0;
    while (i < n && ft_isdigit(str[i]))
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res);
}