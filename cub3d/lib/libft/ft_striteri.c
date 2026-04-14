/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:51:16 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/29 14:14:00 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	if (NULL == s || NULL == f)
		return ;
	while (s[i])
	{
		f(i, s + i);
		++i;
	}
}

/*
int	main(int argc, char **argv)
{
	void	(*f)(unsigned int, char *);

	f = ft_capitalize;
	ft_striteri(argv[1], f);
	printf("%s\n", argv[1]);
}
*/