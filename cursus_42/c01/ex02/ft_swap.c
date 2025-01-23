/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:22:06 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/05 12:29:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
/*
int	main(void)
{
	int	c;
	int	d;
	
	c = 10;
	d = 20;
	printf("avant: c = %d, d = %d\n", c, d);
	ft_swap(&c, &d);
	printf("apres: c = %d, d = %d\n:", c, d);
	return(0);
}
*/
