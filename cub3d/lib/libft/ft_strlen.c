/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:19:51 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 13:24:50 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len ++;
	return (len);
}
/*
int     main(void)
{
	char *s1 = "peanut";
	char *s2 = "nada";

	printf("long %s -> %zu\n", s1, ft_strlen(s1));
	printf("long %s -> %zu\n", s2, ft_strlen(s2));
}
*/