/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:21:21 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/19 20:21:36 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
