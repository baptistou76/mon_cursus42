/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:58:41 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/10 11:58:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	c;
	int	d;

	c = 0;
	if (!to_find[0])
		return (str);
	while (str[c])
	{
		d = 0;
		while (str[c + d] == to_find[d] && str[c + d] && to_find[d])
			d++;
		if (!to_find[d])
			return (&str[c]);
		c++;
	}
	return (0);
}
/*
 int	main(void)
 {
 	char	test[] = "bonjour tout le monde";
 	char	find[] = "1";
 	
 	printf("avant test: %s\n", test);
 	printf("apres test: %s\n", ft_strstr(test, find));
 	return (0);
 }
 */
