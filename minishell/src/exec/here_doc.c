/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:13:05 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:27:51 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	made_new_file(int *fd, char **name)
{
	static int	nb_file = 0;
	char		*nb_str;

	nb_str = ft_itoa(nb_file);
	*name = ft_strjoin("/tmp/here_doc_", nb_str);
	free(nb_str);
	*fd = open(*name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	nb_file++;
}

int	if_limiter(char *line, char *limiter)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strcmp(line, limiter) == 0)
		return (0);
	return (1);
}

void	free_path(char *path_cmd)
{
	if (path_cmd != NULL)
		free(path_cmd);
}

int	fill_here_doc_file(int fd, char *delimitor)
{
	char	*line;

	setup_signal_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (g_status == true)
			return (free_path(line), 0);
		if (line == NULL)
		{
			ft_printf(RED ERR_HDOC " (wanted `%s')\n" RESET, delimitor);
			break ;
		}
		if (if_limiter(line, delimitor) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	return (1);
}

char	*get_here_doc(char *str)
{
	char	*file_name;
	char	*delimitor;
	int		here_doc_fd;

	delimitor = ft_strdup(str);
	file_name = NULL;
	made_new_file(&here_doc_fd, &file_name);
	if (here_doc_fd == -1)
		return (ft_printf(RED "error to create a tmp file\n" RESET), NULL);
	fill_here_doc_file(here_doc_fd, delimitor);
	if (g_status == true)
		return (close(here_doc_fd), unlink(file_name), free(delimitor),
			free(file_name), NULL);
	free(delimitor);
	close(here_doc_fd);
	return (file_name);
}
