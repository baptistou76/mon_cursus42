/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:53:01 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/10 01:53:04 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	c;
	unsigned int	d;

	c = 0;
	d = 0;
	while (dest[c] != '\0')
	{
		c++;
	}
	while (src[d] != '\0' && d < nb)
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
	char	dest[30] = "bonjour ";
	char	src[] = "tout le monde";
	unsigned int	nb = 10;

	printf("avant test: %s -> %s\n", dest, src);
	printf("apres test: %s\n", ft_strncat( dest, src, nb));
	return (0);
}
*/
