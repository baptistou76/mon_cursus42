/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:36:48 by bcaumont          #+#    #+#             */
/*   Updated: 2024/10/22 14:07:16 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			total_size;
	size_t			i;
	unsigned char	*char_ptr;

	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	char_ptr = (unsigned char *)ptr;
	i = 0;
	while (i < total_size)
	{
		char_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
