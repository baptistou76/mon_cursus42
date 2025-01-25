/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:11:52 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 14:44:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H


# include <stdarg.h>
# include <unistd.h>

int	ft_print_char(char c);
int	ft_print_str(char *str);
int	ft_print_decimal(int n);
int	ft_print_pointer(void *ptr);
int	ft_printf(const char *format, ...);
int	ft_conversion(char conversion, va_list args);
int	ft_print_hex_up(unsigned int n);
int	ft_print_hex_low(unsigned int n);
int	ft_print_unsigned(unsigned int n);

#endif
