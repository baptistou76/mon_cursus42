/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 00:19:55 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/10 00:19:59 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strcat(char *dest, char *src)
{
	int	c;
	int	d;

	c = 0;
	while (dest[c] != '\0')
	{
		c++;
	}
	d = 0;
	while (src[d] != '\0')
	{
		dest[c] = src[d];
		c++;
		d++;
	}
	dest[c] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char	dest[45] = "ceci est ";
	char	src[] = "mon test";
	
	printf("avant le test: %s -> %s\n", dest, src);
	printf("apres le test: %s\n", ft_strcat(dest, src));
	return (0);
}
*/
