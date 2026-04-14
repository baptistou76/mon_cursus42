/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:49:54 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/29 14:13:21 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		i;

	i = 0;
	if (NULL == s)
		return (NULL);
	ptr = malloc(ft_strlen(s) + 1);
	if (NULL == ptr)
		return (NULL);
	if (NULL == f)
	{
		ft_strlcpy(ptr, s, ft_strlen(s) + 1);
		return (ptr);
	}
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
 *
int	main(int argc, char **argv)
{
	char 	*s;
	char	(*f)(unsigned int, char);	

	f = my_func;
	s = "hello";	
	printf("%s\n", ft_strmapi(s, f));
}
*/