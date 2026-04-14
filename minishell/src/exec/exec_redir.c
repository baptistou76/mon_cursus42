/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:52:40 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 14:47:03 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_management(t_cmd *cmd, int prev_fd)
{
	if (manag_infile(cmd, prev_fd) == 1)
	{
		safe_close(cmd->pipe_fd[READ]);
		safe_close(cmd->pipe_fd[WRITE]);
		return (1);
	}
	if (manag_outfile(cmd, cmd->pipe_fd) == 1)
	{
		safe_close(cmd->pipe_fd[READ]);
		safe_close(cmd->pipe_fd[WRITE]);
		return (1);
	}
	safe_close(cmd->pipe_fd[READ]);
	safe_close(cmd->pipe_fd[WRITE]);
	return (0);
}

void	exec_redirection(t_data *data, t_cmd *cmd, int input_fd, int output_fd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		exit_clean(data);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}
