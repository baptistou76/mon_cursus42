/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:25:51 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 16:17:08 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprint_decimal(int n)
{
	int	len;
	int	temp;

	len = 0;
	temp = n;
	if (n <= 0)
		len++;
	while (temp)
	{
		temp /= 10;
		len++;
	}
	ft_putnbr_fd(n, 1);
	return (len);
}
