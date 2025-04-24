/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:53:12 by marieli           #+#    #+#             */
/*   Updated: 2025/04/23 14:53:23 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex(unsigned long n, int uppercase)
{
	char	digit;
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_putnbr_hex(n / 16, uppercase);
	digit = (n % 16);
	if (digit < 10)
		count += ft_putchar(digit + '0');
	else
	{
		if (uppercase)
			count += ft_putchar(digit - 10 + 'A');
		else
			count += ft_putchar(digit - 10 + 'a');
	}
	return (count);
}