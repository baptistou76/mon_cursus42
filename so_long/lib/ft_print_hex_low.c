/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_low.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:29:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 16:16:18 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex_low(unsigned int n)
{
	size_t	hex_len;
	char	*hex;

	hex_len = 0;
	hex = "0123456789abcdef";
	if (n >= 16)
		hex_len += ft_print_hex_low(n / 16);
	hex_len += write(1, &hex[n % 16], 1);
	return (hex_len);
}
