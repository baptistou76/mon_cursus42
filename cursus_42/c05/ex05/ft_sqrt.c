/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:18:20 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/14 19:18:22 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_sqrt(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		return (0);
	while (i <= nb)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	int	nb1;
	int	nb2;

	nb1 = 25;
	nb2 = 30;
	printf("la racine carre de %d est %d\n", nb1, ft_sqrt(nb1));
	printf("la racine carre de %d est %d\n", nb2, ft_sqrt(nb2));
}
*/
