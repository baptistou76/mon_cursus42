/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:50:36 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 14:03:56 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)(unsigned char *)s + i);
		i++;
	}
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	(void) argc;
	char	c;
	char	*s;
	int		n;
	char	*result;

	s = argv[1];
	c = argv[2][0];
	n = atoi(argv[3]);
	
	result = ft_memchr(s, c, n);
	if (result)
		printf("trouve: '%c'\n", *result);
	else
		printf("pas trouve\n");
}
*/