/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:35:29 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 16:15:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conversion(char conversion, va_list args)
{
	if (conversion == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (conversion == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (conversion == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else if (conversion == 'd' || conversion == 'i')
		return (ft_print_decimal(va_arg(args, int)));
	else if (conversion == 'u')
		return (ft_print_unsigned(va_arg(args, int)));
	else if (conversion == 'x')
		return (ft_print_hex_low(va_arg(args, unsigned int)));
	else if (conversion == 'X')
		return (ft_print_hex_up(va_arg(args, unsigned int)));
	else if (conversion == '%')
		return (ft_print_char('%'));
	return (0);
}
