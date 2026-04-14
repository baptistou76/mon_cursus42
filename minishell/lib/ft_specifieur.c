/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifieur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:10:48 by garside           #+#    #+#             */
/*   Updated: 2025/03/04 19:48:00 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_specifieur(char spe, va_list args)
{
	int	len;

	len = 0;
	if (spe == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (spe == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (spe == 'p')
		len += ft_print_pointeur((unsigned long)va_arg(args, void *));
	else if (spe == 'd' || spe == 'i')
		len += ft_print_number(va_arg(args, int));
	else if (spe == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (spe == 'x')
		len += ft_print_hex(va_arg(args, unsigned int), 0);
	else if (spe == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), 1);
	else if (spe == '%')
		len += ft_putchar('%');
	return (len);
}
