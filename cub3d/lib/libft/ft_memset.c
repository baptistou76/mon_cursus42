/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:41:21 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 13:26:08 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n-- > 0)
		ptr[n] = (unsigned char)c;
	return (s);
}
/*
int     main(void)
{
	char	v[10] = {0};

	ft_memset(v, 42, 5);

	for (int i = 0; i < 10; ++i)
		printf("%d\n", v[i]);
}
*/