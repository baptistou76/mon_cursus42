/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:03:15 by broboeuf          #+#    #+#             */
/*   Updated: 2024/11/11 10:07:07 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(char c);
int	ft_puthex_lower(unsigned long n);
int	ft_puthex_upper(unsigned long n);
int	ft_putnbr(long n);
int	ft_putpointer(void *struggle);
int	ft_putstr(char *s);
int	ft_set_type(const char *format, va_list ap);

#endif