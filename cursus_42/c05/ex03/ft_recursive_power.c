/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:47:51 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/14 17:47:53 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}
/*
int	main(void)
{
	int	result;
	int	nb;
	int	power;
	
	nb = 5;
	power = 5;
	result = ft_recursive_power(nb,power);
	printf("la puissance de %d par %d est %d\n", nb, power, result);
	nb = 2;
	power = 4;
	result = ft_recursive_power(nb, power);
	printf("la puissance de %d par %d est %d\n", nb, power, result);
}
*/
