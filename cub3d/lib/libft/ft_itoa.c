/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:51:08 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/29 14:54:03 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		++count;
	while (n)
	{
		++count;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;

	len = ft_len(n);
	ptr = malloc(len + 1);
	if (NULL == ptr)
		return (NULL);
	ptr[len] = '\0';
	if (0 == n)
		ptr[0] = '0';
	else if (n < 0)
		ptr[0] = '-';
	while (n)
	{
		if (n < 0)
			ptr[--len] = (~(n % 10) + 1) + 48;
		else
			ptr[--len] = (n % 10) + 48;
		n /= 10;
	}
	return (ptr);
}

/*
int main()
{
  char *str = ft_itoa(-2134);
  printf("%s\n", str);

  str = ft_itoa(42);
  printf("%s\n", str);
  str = ft_itoa(707);
  printf("%s\n", str);

  str = ft_itoa(INT32_MIN);
  printf("%s\n", str);

  str = ft_itoa(INT32_MAX);
  printf("%s\n", str);
  
  str = ft_itoa(0);
  printf("%s\n", str);

  return 0;
}
*/