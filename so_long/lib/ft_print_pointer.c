/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:42:01 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 16:15:24 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_put_hex(unsigned long num)
{
	char	*hex_digits;
	int		count;

	hex_digits = "0123456789abcdef";
	count = 0;
	if (num >= 16)
		count += ft_put_hex(num / 16);
	count += ft_print_char(hex_digits[num % 16]);
	return (count);
}

int	ft_print_pointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_print_str("(nil)"));
	count += ft_print_str("0x");
	count += ft_put_hex((unsigned long)ptr);
	return (count);
}
