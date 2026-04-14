/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:31:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:36:57 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manag_infile(t_cmd *cmd, int prev_fd)
{
	int	in_fd;

	if (cmd->infile == NULL && prev_fd == 0)
		return (0);
	if (cmd->infile == NULL && prev_fd != 0)
		return (dup2(prev_fd, READ), safe_close(prev_fd), 0);
	if (prev_fd != 0)
		safe_close(prev_fd);
	in_fd = last_infile(cmd);
	if (in_fd == -1)
		return (1);
	return (dup2(in_fd, READ), safe_close(in_fd), 0);
}

int	open_infile(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		if (access(str, F_OK) == -1)
		{
			no_such_file_or_directory(str);
		}
		else if (access(str, R_OK) == -1)
			permission_denied(str);
		else
			error_message(str);
	}
	return (fd);
}

int	last_infile(t_cmd *cmd)
{
	int		fd;
	int		prev_fd;
	t_redir	*infile;

	prev_fd = -1;
	infile = cmd->infile;
	while (infile)
	{
		fd = open_infile(infile->file);
		if (fd == -1)
		{
			if (prev_fd != -1)
				safe_close(prev_fd);
			return (-1);
		}
		if (prev_fd != -1)
			safe_close(prev_fd);
		prev_fd = fd;
		infile = infile->next;
	}
	return (fd);
}
