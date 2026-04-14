/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:06:28 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/16 08:54:35 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != c)
		++s;
	if (*s != '\0' || c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (n == 0 || dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s)
	{
		while (n--)
		{
			d[n] = s[n];
		}
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strcat(char **dest_pointer, const char *src)
{
	size_t	dest_len;
	size_t	src_len;
	char	*new_dest;

	if (*dest_pointer == NULL)
		dest_len = 0;
	else
		dest_len = ft_strlen(*dest_pointer);
	src_len = ft_strlen(src);
	new_dest = malloc(dest_len + src_len + 1);
	if (new_dest)
	{
		ft_memmove(new_dest, *dest_pointer, dest_len);
		ft_memmove(new_dest + dest_len, src, src_len);
		new_dest[dest_len + src_len] = '\0';
	}
	free(*dest_pointer);
	*dest_pointer = new_dest;
}
