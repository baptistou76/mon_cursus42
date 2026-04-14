/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_dprintf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:52:55 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 16:16:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conversion_dprintf(char conversion, va_list args)
{
	if (conversion == 'c')
		return (ft_dprint_char(va_arg(args, int)));
	else if (conversion == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (conversion == 'd' || conversion == 'i')
		return (ft_print_decimal(va_arg(args, int)));
	else if (conversion == '%')
		return (ft_print_char('%'));
	return (0);
}
