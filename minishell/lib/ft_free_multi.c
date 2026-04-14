/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:55:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 16:13:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_multi(int n, ...)
{
	va_list	args;
	void	*ptr;
	int		i;

	va_start(args, n);
	i = 0;
	while (i < n)
	{
		ptr = va_arg(args, void *);
		if (ptr)
			free(ptr);
		i++;
	}
	va_end(args);
}
