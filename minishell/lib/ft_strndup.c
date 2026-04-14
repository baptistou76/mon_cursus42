/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:24:34 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 13:24:36 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int j)
{
	char	*pnt;
	int		i;

	pnt = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!pnt)
		return (NULL);
	i = 0;
	while (s1[i] && i < j)
	{
		pnt[i] = s1[i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}
