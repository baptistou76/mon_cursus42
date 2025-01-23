/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:20:18 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/14 18:20:22 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_fibonacci(int index)
{
	if (index < 0)
	{
		return (-1);
	}
	else if (index == 0)
	{
		return (0);
	}
	else if (index == 1)
	{
		return (1);
	}
	else
	{
		return (ft_fibonacci(index -1) + ft_fibonacci(index -2));
	}
}
/*
int	main(void)
{
	int	n = 10;
	int	result = ft_fibonacci(n);
	printf("le %d-ieme element de la suite de fibonacci est : %d\n", n, result);
	return (0);
}
*/	
