/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:02:17 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/11 18:02:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(char *str)
{
	int	c;
	int	sign;
	int	result;

	c = 0;
	sign = 1;
	result = 0;
	while (str[c] != '\0' && str[c] == ' ')
		c++;
	while (str[c] && (str[c] == '-' || str[c] == '+'))
	{
		if (str[c] == '-')
			sign = -1;
		c++;
	}
	while (str[c] && (str[c] >= '0' && str[c] <= '9'))
	{
		result = result * 10 + (str[c] - '0');
		c++;
	}
	return (sign * result);
}
/*
int	main(void)
{
	char	test[] = "  --+--+1234ab567";
	
	printf("%d\n", ft_atoi(test));
	return (0);
}
*/
