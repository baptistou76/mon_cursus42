/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:57:41 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/20 11:31:14 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	secure_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("Fork failed");
	return (pid);
}

void	secure_dup2(int old_fd, int new_fd)
{
	if (old_fd < 0)
		ft_perror("dup2: invalid fd");
	if (dup2(old_fd, new_fd) == -1)
		ft_perror("dup2 failed");
}

int	secure_open(char *filename, int flags)
{
	int	fd;

	if (!filename)
	{
		ft_putstr_fd("Pipex:filename is NULL", 2);
		return (-1);
	}
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Pipex: ", 2);
		perror(filename);
		return (-1);
	}
	return (fd);
}

void	secure_close(int fd)
{
	if (fd < 0)
		return ;
	if (close(fd) == -1)
		ft_perror("Close failed");
}

int	file_is_executable(char *file)
{
	if (access(file, X_OK) == 0)
		return (1);
	return (0);
}
