/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:15:22 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/16 10:15:24 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_power(int nb, int power)
{
	int	result;

	if (power < 0)
		return (0);
	if (nb == 0 && power == 0)
		return (1);
	result = 1;
	while (power > 0)
	{
		result *= nb;
		power--;
	}
	return (result);
}
/*
int	main(void)
{
	int	nb;
	int	power;
	int	result;

	nb = 5;
	power = 5;
	result = ft_iterative_power(nb, power);
	printf("le resultat de %d puissance %d est %d\n", nb, power, result);
	nb = 2;
	power = 4;
	result = ft_iterative_power(nb, power);
	printf("le resultat de %d puissance %d est %d\n", nb, power, result);
}
*/
