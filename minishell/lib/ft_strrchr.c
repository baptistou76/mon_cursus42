/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:18:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/03 15:09:42 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	find;
	char	*last_occurence;
	int		i;

	find = (char)c;
	last_occurence = (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == find)
			last_occurence = (char *)s;
		s++;
	}
	if (find == '\0')
		return ((char *)s);
	return (last_occurence);
}
