/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:32 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/09 13:51:35 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	c;

	c = 0;
	while (s1[c] != '\0' && s2[c] != '\0')
	{
		if (s1[c] != s2[c])
		{
			return (s1[c] - s2[c]);
		}
		c++;
	}
	if (s1[c] != '\0' || s2[c] != '\0')
	{
		return (s1[c] - s2[c]);
	}
	return (0);
}
/*
int	main(void)
{
	char	test1[] = "bonjour ca va ";
	char	test2[] = "bon";
	
	printf("avant le test: %s\n", test1);
	printf("avant le test: %s\n", test2);
	printf("apres le test: %d\n", ft_strcmp(test1, test2));
	return (0);
}
*/
