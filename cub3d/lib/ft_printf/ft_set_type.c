/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:15:28 by broboeuf          #+#    #+#             */
/*   Updated: 2024/11/11 12:14:31 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_set_type(const char *format, va_list ap)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (*format == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (*format == 'p')
		count += ft_putpointer(va_arg(ap, void *));
	else if (*format == 'd' || *format == 'i')
		count += ft_putnbr(va_arg(ap, int));
	else if (*format == 'u')
		count += ft_putnbr(va_arg(ap, unsigned int));
	else if (*format == 'x')
		count += ft_puthex_lower(va_arg(ap, unsigned int));
	else if (*format == 'X')
		count += ft_puthex_upper(va_arg(ap, unsigned int));
	else if (*format == '%')
		count += ft_putchar('%');
	return (count);
}
