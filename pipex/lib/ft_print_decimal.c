/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:42:37 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 16:14:54 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_recursive(int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_recursive(n / 10);
	count += ft_print_char((n % 10) + '0');
	return (count);
}

int	ft_print_decimal(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (ft_print_str("-2147483648"));
	if (n < 0)
	{
		count += ft_print_char('-');
		n = -n;
	}
	count += ft_putnbr_recursive(n);
	return (count);
}
