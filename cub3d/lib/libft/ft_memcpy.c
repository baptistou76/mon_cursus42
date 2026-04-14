/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:50:26 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/29 17:24:30 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;

	i = 0;
	if (NULL == src && NULL == dst)
		return (NULL);
	while (n--)
		*((unsigned char *)dst + i++) = *(unsigned char *)src++;
	return (dst);
}
/*
int     main(void)
{
	char	v[] = "peanut";
	char	v1[] = "butter";

	printf("%s ->%p\n", v,  ft_memcpy(v, v1, 3));
}
*/