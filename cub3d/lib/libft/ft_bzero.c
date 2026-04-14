/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:35:38 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 13:27:07 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
		*((unsigned char *)s + n) = 0;
}
/*
int     main(void)
{
	int		v[10];

	for (int i = 0; i < 10; ++i)
		v[i] = 42;

	for (int i = 0; i < 10; ++i)
		printf("%d\n", v[i]);
	puts("");

	ft_bzero(v, 40);

	for (int i = 0; i < 10; ++i)
		printf("%d\n", v[i]);
}
*/