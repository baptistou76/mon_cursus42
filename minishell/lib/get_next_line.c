/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:55:40 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 02:55:58 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	int			read_byte;

	str = NULL;
	read_byte = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = process_buffer(buffer, str);
	while (read_byte > 0 && is_new_line(buffer) == 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)
			return (free(str), NULL);
		if (read_byte == 0)
		{
			if (str != NULL && str[0] != '\0')
				return (str);
			return (free(str), NULL);
		}
		buffer[read_byte] = '\0';
		str = ft_strjoin_gnl(str, buffer);
	}
	return (str);
}
