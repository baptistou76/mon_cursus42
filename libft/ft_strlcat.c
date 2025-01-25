/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:16:21 by bcaumont          #+#    #+#             */
/*   Updated: 2024/10/16 15:26:17 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_l;
	size_t	src_l;
	size_t	count;

	dst_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	count = 0;
	if (size <= dst_l)
		return (size + src_l);
	while (src[count] && dst_l + count < size - 1)
	{
		dst[dst_l + count] = src[count];
		count++;
	}
	dst[dst_l + count] = '\0';
	return (dst_l + src_l);
}
