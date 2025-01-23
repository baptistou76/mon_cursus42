/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:57:28 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/12 00:57:31 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_factorial(int nb)
{
	int	result;

	result = 1;
	if (nb < 0)
		return (0);
	while (nb > 0)
	{
		result = result * nb;
		nb--;
	}
	return (result);
}
/*
int	main(void)
{
	int	result;
	int	nb;
	
	nb = 5;
	result = ft_iterative_factorial(nb);
	printf("la factorielle de %d est %d\n", nb, result);
	nb = 0;
	result = ft_iterative_factorial(nb);
	printf("la factorielle de %d est %d\n", nb, result);
	nb = 10;
	result = ft_iterative_factorial(nb);
	printf("la factorielle de %d est %d\n", nb, result);
	return (0);
}
*/
