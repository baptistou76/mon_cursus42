/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:10:45 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/14 20:10:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_is_prime(int nb)
{
	int	i;

	if (nb <= 1)
		return (0);
	i = 2;
	while (i * i <= nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}
/*
int	main(void)
{
	int	nb1 = 3;
	int	nb2 = 8;
	int	nb3 = 7;
	
	printf(" le nombre %d est un %d\n", nb1, ft_is_prime(nb1));
	printf(" le nombre %d est un %d\n", nb2, ft_is_prime(nb2));
	printf(" le nombre %d est un %d\n", nb3, ft_is_prime(nb3));
	return (0);
}
*/
