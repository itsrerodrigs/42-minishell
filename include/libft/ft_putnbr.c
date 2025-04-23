/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:54:06 by marieli           #+#    #+#             */
/*   Updated: 2025/03/20 17:54:51 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	long	num;
	int		count;

	count = 0;
	num = n;
	if (num < 0)
	{
		count += ft_putchar('-');
		num = -num;
	}
	if (num > 9)
		count += ft_putnbr(num / 10);
	count += ft_putchar('0' + (num % 10));
	return (count);
}

int	ft_putnbr_u(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr_u(n / 10);
	count += ft_putchar('0' + (n % 10));
	return (count);
}

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
