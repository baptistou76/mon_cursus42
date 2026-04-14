/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:51:55 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/29 17:38:19 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((NULL == src && NULL == dst) || len == 0)
		return (dst);
	if (dst > src)
		while (len--)
			*((unsigned char *)dst + len) = *((unsigned char *)src + len);
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
/*
int     main(void)
{
	char	src[] = "klaatu verata nikto";
	char	*dest;

	dest = src + 8;
	printf("%s\n", (char *)ft_memmove(src, dest, 11));
}
*/