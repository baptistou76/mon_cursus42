/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:16:57 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/07 13:36:04 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != c)
		s++;
	if (*s != '\0' || c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
		*(char *)dest++ = *(char *)src++;
	return ((void *)(char *)dest - i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strcat(char **dest_ptr, const char *src)
{
	size_t	dest_len;
	size_t	src_len;
	char	*result;

	dest_len = ft_strlen(*dest_ptr);
	src_len = ft_strlen(src);
	result = malloc(dest_len + src_len + 1);
	if (result)
	{
		ft_memcpy(result, *dest_ptr, dest_len);
		ft_memcpy(result + dest_len, src, src_len);
		result[dest_len + src_len] = '\0';
	}
	free(*dest_ptr);
	*dest_ptr = result;
}
