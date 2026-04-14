/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:01 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 15:05:54 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < count * size)
		tmp[i++] = 0;
	return (tmp);
}
/*
int	main(void)
{
	void	*ptrc;
	void	*ptrm;
	int		i;

	ptrc = calloc(3, 4);
	ptrm = malloc(12);
	i = 0;
	while (i < 12)
	{
		printf("%c__", ((char *)ptrm)[i] + 48);
		printf("%c\n", ((char *)ptrc)[i] + 48);
		i++;
	}
}
*/