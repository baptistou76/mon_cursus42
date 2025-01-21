/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:39:42 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/21 13:50:56 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*_fd_reader_to_line(int fd, char *buffer);
char	*_buffer_rest(char *buffer);
void	_buffer_into_line(char **line, char *buffer);

char	*get_next_line(int fd)
{
	static char	fd_buffer[FD_LIMIT][BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = _fd_reader_to_line(fd, fd_buffer[fd]);
	if (line == NULL)
		return (NULL);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

void	_buffer_into_line(char **line, char *buffer)
{
	char	*new_position;
	size_t	updated_buffer;
	char	saved_char;

	new_position = ft_strchr(buffer, '\n');
	if (new_position != NULL)
	{
		saved_char = new_position[1];
		new_position[1] = '\0';
		ft_strcat(line, buffer);
		if (*line == NULL)
			return ;
		new_position[1] = saved_char;
		new_position++;
	}
	else
	{
		ft_strcat(line, buffer);
		if (*line == NULL)
			return ;
		new_position = buffer + ft_strlen(buffer);
	}
	updated_buffer = ft_strlen(new_position);
	ft_memmove(buffer, new_position, updated_buffer);
	buffer[updated_buffer] = '\0';
}

char	*_buffer_rest(char *buffer)
{
	char	*line;
	size_t	line_size;

	line = ft_strchr(buffer, '\n');
	if (line == NULL)
		line = ft_strchr(buffer, '\0');
	line_size = line - buffer + (*line == '\n');
	line = (char *)malloc(line_size + 1);
	if (line == NULL)
		return (NULL);
	ft_memmove(line, buffer, line_size);
	line[line_size] = '\0';
	ft_memmove(buffer, buffer + line_size, BUFFER_SIZE - line_size);
	buffer[BUFFER_SIZE - line_size] = '\0';
	return (line);
}

char	*_fd_reader_to_line(int fd, char *buffer)
{
	char	*line;
	long	byte_read;

	line = _buffer_rest(buffer);
	if (line == NULL)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(line), NULL);
		buffer[byte_read] = '\0';
		if (byte_read == 0 || ft_strchr(buffer, '\n'))
			return (_buffer_into_line(&line, buffer), line);
		if (line == NULL)
			return (NULL);
		ft_strcat(&line, buffer);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}
