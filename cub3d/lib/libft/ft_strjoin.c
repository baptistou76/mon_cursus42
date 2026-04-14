/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:50:14 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/26 14:08:26 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	buffer;
	size_t	i;
	char	*ptr;

	i = 0;
	if (NULL == s1 || NULL == s2)
		return (NULL);
	buffer = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = malloc(buffer * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (*s1)
		*(ptr + i++) = *s1++;
	while (*s2)
		*(ptr + i++) = *s2++;
	*(ptr + i) = '\0';
	return (ptr);
}
/*
int	main(int argc, char **argv)
{
	char *s;
	char *s1;
	char *rest;

	if(argc == 3)
	{char *ft_strtrim(char const *s1, char const *set);
		s = argv[1];
		s1 = argv[2];
	}
	else
	{
		s = "klaatu verata";
		s1 = " nicoughcough";
	}
	
	rest = ft_strjoin(s, s1);
	if (rest)
	{
		printf("%s\n", rest);
		free(rest);
	}
	return(0);
}
*/