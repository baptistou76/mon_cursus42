/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:29:42 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 14:01:53 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main(int argc, char **argv)
{
	(void) argc;
	char	*s;
	char 	*s1;
	int		n;

	s = argv[1];
	s1 = argv[2];
	n = atoi(argv[3]);
	if (ft_strncmp(s, s1, n))
		printf("The strings are not equal\n");
	else 
		 printf("The strings are equal\n");
	if (ft_strncmp(s, s1, n))
		printf("The strings are not equal\n");
	else 
		 printf("The strings are equal\n");
	ft_strncmp("test\200", "test\0", 6);	
}
*/