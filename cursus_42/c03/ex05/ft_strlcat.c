/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:18:00 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/10 14:18:04 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int	ft_stringcount(char *str)
{
	unsigned int	c;

	c = 0;
	while (str[c])
		c++;
	return (c);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_l;
	unsigned int	src_l;
	unsigned int	c;

	dest_l = ft_stringcount(dest);
	src_l = ft_stringcount(src);
	c = 0;
	if (size <= dest_l)
		return (size + src_l);
	while (src[c] && dest_l + c < size - 1)
	{
		dest[dest_l + c] = src[c];
		c++;
	}
	dest[dest_l + c] = '\0';
	return (dest_l + src_l);
}
/*
int	main(void)
{
	char	dest[] = "bonjour tout le monde ";
	char	src[] = "comment ca va ?";
	unsigned int	size = 50;
	
	printf("avant test: %s - %s\n", dest, src);
	printf("apres test: %u\n", ft_strlcat(dest, src, size));
	printf("apres fonction: %s\n", dest);
	return (0);
}
*/
