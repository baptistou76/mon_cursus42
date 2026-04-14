/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:36:39 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/29 15:13:48 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (-2147483648 == n)
		{
			ft_putstr_fd("-2147483648", fd);
			return ;
		}
		n *= -1;
		write(fd, "-", 1);
	}
	if (0 == n)
		write(fd, "0", 1);
	else if (n > 0 && n < 10)
		ft_putchar_fd((n + 48), fd);
	else
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
}

/*
int	main()
{
	ft_putnbr_fd(404, 1);	
	write(1, "\n", 1);
	ft_putnbr_fd(-2147483648, 1);	
	write(1, "\n", 1);
	ft_putnbr_fd(2147483647, 1);	
	write(1, "\n", 1);
	ft_putnbr_fd(0, 1);	
}
*/