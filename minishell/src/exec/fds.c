/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:48:44 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:36:45 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_fds(int prev_fd, int pipe_read, int pipe_write)
{
	if (prev_fd != -1)
		safe_close(prev_fd);
	safe_close(pipe_read);
	safe_close(pipe_write);
}

void	fds_redirection(t_cmd *cmd, int *prev_fd)
{
	if (cmd->next != NULL)
	{
		if (*prev_fd != -1)
			safe_close(*prev_fd);
		*prev_fd = cmd->pipe_fd[READ];
	}
	else
	{
		safe_close(cmd->pipe_fd[READ]);
		if (*prev_fd != -1)
			safe_close(*prev_fd);
	}
}

void	safe_close(int fd)
{
	if (fd >= 0)
	{
		close(fd);
	}
}
