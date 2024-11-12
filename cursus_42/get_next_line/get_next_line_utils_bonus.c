/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:37:41 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/07 15:38:30 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != c)
		++s;
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
	return ((void *)((char *)dest - i));
}

size_t	ft_strlen(const char *s)
{
	const char	*org = s;

	while (*s)
		++s;
	return (s - org);
}

void	ft_strcat(char **dst_ptr, const char *src)
{
	size_t	dst_len;
	size_t	src_len;
	char	*ans;

	dst_len = ft_strlen(*dst_ptr);
	src_len = ft_strlen(src);
	ans = malloc(dst_len + src_len + 1);
	if (ans)
	{
		ft_memcpy(ans, *dst_ptr, dst_len);
		ft_memcpy(ans + dst_len, src, src_len);
		ans[dst_len + src_len] = '\0';
	}
	free(*dst_ptr);
	*dst_ptr = ans;
}
