/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:19:41 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 14:05:23 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s1 + i) != *((unsigned char *)s2 + i))
			return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
		++i;
	}
	return (0);
}
/*
int	main(int argc, char **argv)
{
	(void) argc;
	char	*s = argv[1];
	char	*s1 = argv[2];
	int		n = atoi(argv[3]);
	
	if (!ft_memcmp(s, s1, n))
		printf("The string are equal up to %d letters\n\n\n", n);
	else 
		printf("The strings are different\n\n\n");
}
*/