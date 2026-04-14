/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:10:23 by broboeuf          #+#    #+#             */
/*   Updated: 2024/11/11 12:14:28 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_upper(unsigned long n)
{
	int		i;
	int		count;
	char	buffer[64];

	i = 0;
	count = 0;
	if (n == 0)
		return (write(1, ("0"), 1));
	while (n > 15)
	{
		buffer[i++] = (n % 16);
		n /= 16;
	}
	buffer[i] = n;
	while (i >= 0)
	{
		if (buffer[i] >= 0 && buffer[i] <= 9)
			count += ft_putchar(buffer[i] + 48);
		else if (buffer[i] >= 10 && buffer[i] <= 15)
			count += ft_putchar(buffer[i] + 55);
		i--;
	}
	return (count);
}
