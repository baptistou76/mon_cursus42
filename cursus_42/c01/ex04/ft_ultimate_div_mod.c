/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:32:36 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/06 20:36:42 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	temp;
		
	temp = *a / *b;
	*b = *a % *b;
	*a = temp;
}
/*
int	main(void)
{
	int c;
	int d;
	
	c = 54;
	d = 5;
	printf("avant: c = %d, d = %d\n", c, d);
	ft_ultimate_div_mod(&c, &d);
	printf("apres: c = %d, d = %d\n", c, d);
	return(0);
}
*/
