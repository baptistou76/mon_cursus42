/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointeur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:03:20 by garside           #+#    #+#             */
/*   Updated: 2025/03/11 18:23:50 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_pointeur(unsigned long ptr)
{
	const char	*hex_chars;
	char		buffer[16];
	int			i;
	int			len;

	i = 0;
	len = 2;
	hex_chars = "0123456789abcdef";
	if (!ptr)
		return (write(1, "(nil)", 5));
	if (ptr == 0)
		return (write(1, "0x0", 3));
	write(1, "0x", 2);
	while (ptr > 0)
	{
		buffer[i++] = hex_chars[ptr % 16];
		ptr /= 16;
	}
	while (i > 0)
	{
		write(1, &buffer[--i], 1);
		len++;
	}
	return (len);
}
