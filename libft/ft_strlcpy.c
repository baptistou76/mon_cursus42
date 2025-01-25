/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:15:59 by bcaumont          #+#    #+#             */
/*   Updated: 2024/10/19 11:05:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	c;
	size_t	src_len;

	c = 0;
	if (size > 0)
	{
		while (c < size - 1 && src[c])
		{
			dst[c] = src[c];
			c++;
		}
		dst[c] = '\0';
	}
	src_len = 0;
	while (src[src_len])
		src_len++;
	return (src_len);
}
