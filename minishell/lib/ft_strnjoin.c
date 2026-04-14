/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:24:03 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 13:24:13 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int i)
{
	int		s1_len;
	int		s3_len;
	char	*s3;
	int		k;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s3_len = ft_strlen(s1) + i;
	s3 = malloc((s3_len + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	ft_bzero(s3, s3_len + 1);
	k = 0;
	j = 0;
	while (k < s3_len)
	{
		if (k < s1_len)
			s3[k] = s1[k];
		else
			s3[k] = s2[j++];
		k++;
	}
	return (s3);
}
