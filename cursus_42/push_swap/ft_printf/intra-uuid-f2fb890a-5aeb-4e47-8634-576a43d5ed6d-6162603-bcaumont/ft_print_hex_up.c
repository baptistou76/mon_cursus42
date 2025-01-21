/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:06:35 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/05 14:29:51 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_up(unsigned int n)
{
	size_t	hex_len;
	char	*hex;

	hex_len = 0;
	hex = "0123456789ABCDEF";
	if (n >= 16)
		hex_len += ft_print_hex_up(n / 16);
	hex_len += write(1, &hex[n % 16], 1);
	return (hex_len);
}
