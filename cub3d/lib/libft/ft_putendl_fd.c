/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:39:57 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/29 17:31:24 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
		write(fd, "\n", 1);
	}
}

/*
int	main()
{
	ft_putendl_fd("hello", 0);
	ft_putendl_fd("hello", 1);
	ft_putendl_fd("hello", 2);
	//3 not in terminal
	ft_putendl_fd("hello", 3);
}
*/