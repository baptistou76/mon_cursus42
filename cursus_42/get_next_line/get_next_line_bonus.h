/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:32:02 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/07 15:34:37 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_LIMIT 1024

typedef unsigned char	t_uchar;
typedef unsigned char	t_byte;

char					*ft_strchr(const char *s, int c);
void					*ft_memcpy(void *dest, const void *src, size_t n);
size_t					ft_strlen(const char *s);
void					ft_strcat(char **dest, const char *src);
char					*get_next_line(int fd);

#endif