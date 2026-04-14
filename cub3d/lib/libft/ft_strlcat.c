/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:20:00 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 13:45:20 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t count)
{
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (NULL == dest && 0 == count)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (dest_len >= count)
		return (src_len + count);
	else
		count -= dest_len;
	ft_strlcpy(dest + dest_len, src, count);
	return (dest_len + src_len);
}
/*
int     main(void)
{
	char dest[50] = "Hello";
	char src[] = "World";
	
	unsigned int result = ft_strlcat(dest, src, sizeof(dest));
	
	printf("dest apres concatenation : %s\n", dest);
	printf("taille totale après concaténation : %u\n", result);
	return 0;
}
*/