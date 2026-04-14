/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:49:46 by garside           #+#    #+#             */
/*   Updated: 2025/03/11 18:23:46 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int n, int uppercase)
{
	char	*hex_chars;
	int		len;

	if (uppercase)
		hex_chars = "0123456789ABCDEF";
	else
		hex_chars = "0123456789abcdef";
	len = 0;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n >= 16)
		len += ft_print_hex(n / 16, uppercase);
	ft_putchar(hex_chars[n % 16]);
	return (len + 1);
}
