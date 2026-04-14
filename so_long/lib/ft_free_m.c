/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:13:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 13:13:04 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_m(int n, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, n);
	while (i < n)
	{
		free(va_arg(args, void *));
		i++;
	}
	va_end(args);
}
