/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:09:04 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/09 22:09:10 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	c;

	c = 0;
	while (c < n && s1[c] != '\0' && s2[c] != '\0')
	{
		if (s1[c] != s2[c])
		{
			return (s1[c] - s2[c]);
		}
		c++;
	}
	if (c < n)
	{
		if (s1[c] != '\0')
			return (s1[c]);
		if (s2[c] != '\0')
			return (-s2[c]);
	}
	return (0);
}
/*
int	main(void)
{
	char	test0[] = "bonjour";
	char	test1[] = "bonjour";
	char	test2[] = "bons";
	char	test3[] = "";
	
	printf("test1: (n=3): %d\n", ft_strncmp(test0, test1, 3));
	printf("test2: (n=3): %d\n", ft_strncmp(test1, test2, 6));
	printf("test3: (n=3): %d\n", ft_strncmp(test2, test3, 3));
	return (0);
}
*/
