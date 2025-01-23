/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:15:50 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/11 15:15:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_putstr(char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\0')
	{
		write (1, &str[c], 1);
		c++;
	}
}
/*
int	main(void)
{
	char	test0[] = "et voila... ";
	char	test1[] = "ca s'affiche.";
	
	ft_putstr(test0);
	ft_putstr(test1);
	return (0);
}
*/
