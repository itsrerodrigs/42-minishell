<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:41:48 by marieli           #+#    #+#             */
/*   Updated: 2025/04/23 14:42:16 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_putnbr_u(unsigned int n)
{
    int count;

    count = 0;
    if (n > 9)
        count += ft_putnbr_u(n / 10);
    count += ft_putchar('0' + (n % 10));
    return (count);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:41:48 by marieli           #+#    #+#             */
/*   Updated: 2025/04/23 14:42:16 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_putnbr_u(unsigned int n)
{
    int count;

    count = 0;
    if (n > 9)
        count += ft_putnbr_u(n / 10);
    count += ft_putchar('0' + (n % 10));
    return (count);
}
>>>>>>> dev_parsing
