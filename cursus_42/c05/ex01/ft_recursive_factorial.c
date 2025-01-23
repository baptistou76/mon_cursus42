/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:18:40 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/12 01:18:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_recursive_factorial(int nb)
{
	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	return (nb * ft_recursive_factorial(nb - 1));
}
/*
int	main(void)
{
	int	result;
	int	nb;
	
	nb = 5;
	result = ft_recursive_factorial(nb);
	printf("la factorielle de %d est %d\n", nb, result);
	nb = 0;
	result = ft_recursive_factorial(nb);
	printf("la factorielle de %d est %d\n", nb, result);
	nb = 10;
	result = ft_recursive_factorial(nb);
	printf("la factorielle de %d est %d\n", nb, result);
}
*/
