/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:20:10 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/03 15:09:24 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;
	size_t	little_len;
	char	*p_big;

	i = 0;
	p_big = (char *)big;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return (p_big);
	while (p_big[i] && i < len)
	{
		y = 0;
		while (p_big[i + y] && little[y] && p_big[i + y] == little[y] && (i
				+ y) < len)
		{
			y++;
		}
		if (y == little_len)
			return (p_big + i);
		i++;
	}
	return (NULL);
}
