/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:15:09 by broboeuf          #+#    #+#             */
/*   Updated: 2024/11/11 12:14:29 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long n)
{
	int		i;
	int		count;
	char	buffer[64];

	i = 0;
	count = 0;
	if (n == 0)
		count += write(1, "0", 1);
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (--i >= 0)
	{
		count += ft_putchar(buffer[i]);
	}
	return (count);
}
