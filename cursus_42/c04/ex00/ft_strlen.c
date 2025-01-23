/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:00:02 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/11 15:00:05 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}
/*
int	main(void)
{
	char	test0[] = "ceci est mon test pour strlsn";
	char	test1[] = "i";
	
	printf("test0: %d\n", ft_strlen(test0));
	printf("test1: %d\n", ft_strlen(test1));
	return (0);
}
*/	
