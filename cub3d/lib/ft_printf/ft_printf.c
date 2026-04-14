/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:01:23 by broboeuf          #+#    #+#             */
/*   Updated: 2025/01/09 18:41:22 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_format(const char *format)
{
	if ((*format == 'c') || (*format == 's') || (*format == 'p')
		|| (*format == 'd') || (*format == 'i') || (*format == 'u')
		|| (*format == 'x') || (*format == 'X' || (*format == '%')))
		return (1);
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (check_format(format) == 1)
			{
				count += ft_set_type(format, ap);
				format++;
			}
		}
		else
		{
			count += ft_putchar(*format);
			format++;
		}
	}
	va_end(ap);
	return (count);
}

int	main(void)
{
	int	count;
	int	*ptr;

	count = ft_printf("Test %c\n", 'A');
	ft_printf("Characters printed: %d\n", count);
	count = ft_printf("Test %s\n", "Hello, world!");
	ft_printf("Characters printed: %d\n", count);
	count = ft_printf("Test %d\n", 1234);
	ft_printf("Characters printed: %d\n", count);
	count = ft_printf("Test %x\n", 255);
	ft_printf("Characters printed: %d\n", count);
	ptr = NULL;
	count = ft_printf("Test %p\n", ptr);
	ft_printf("Characters printed: %d\n", count);
	count = ft_printf("Test %%\n");
	ft_printf("Characters printed: %d\n", count);
	return (0);
}
