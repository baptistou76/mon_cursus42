/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:03:30 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 14:29:18 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	k;

	j = 0;
	if (!*little || (NULL == big && !len))
		return ((char *)big);
	while (*(big + j) && j < len)
	{
		k = 0;
		while (*(big + j + k) == *(little + k) && (k + j) < len)
		{
			if (0 == *(little + k + 1))
				return ((char *)big + j);
			++k;
		}
		++j;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", ft_strnstr("klaatu verata nikto", "verata", 19));
}
*/