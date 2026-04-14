/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:12:36 by broboeuf          #+#    #+#             */
/*   Updated: 2024/11/11 12:23:11 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(void *p)
{
	int	counter;

	counter = 0;
	if (p == 0)
		return (ft_putstr("(nil)"));
	counter += write(1, "0x", 2);
	counter += ft_puthex_lower((long int)p);
	return (counter);
}
