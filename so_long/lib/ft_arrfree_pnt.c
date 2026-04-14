/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree_pnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:11:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/01 13:11:31 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrfree_pnt(void **arr)
{
	int	arr_len;
	int	i;

	arr_len = ft_arrlen_pnt((void **)arr);
	i = 0;
	while (i < arr_len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
