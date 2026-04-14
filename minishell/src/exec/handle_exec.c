/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:02:17 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 14:58:15 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_single_command(t_data *data, t_cmd *cmd, int prev_fd)
{
	if (cmd->next == NULL)
	{
		cmd->saved_stdin = dup(STDIN_FILENO);
		cmd->saved_stdout = dup(STDOUT_FILENO);
		if (cmd->saved_stdin < 0 || cmd->saved_stdout < 0)
			return (perror("dup"), CODE_FAIL);
		if (redirect_management(cmd, prev_fd) == 1)
		{
			safe_close(cmd->saved_stdin);
			safe_close(cmd->saved_stdout);
			return (CODE_FAIL);
		}
		data->last_status = which_command(data, cmd, prev_fd);
		dup2(cmd->saved_stdin, STDIN_FILENO);
		dup2(cmd->saved_stdout, STDOUT_FILENO);
		safe_close(cmd->saved_stdin);
		safe_close(cmd->saved_stdout);
		return (data->last_status);
	}
	return (0);
}

int	handle_path_exec(t_data *data, t_cmd *cmd)
{
	if (access(cmd->path, F_OK) == -1)
		return (126);
	if (access(cmd->path, X_OK == -1))
	{
		return (permission_denied(cmd->args[0]), 126);
	}
	else
		execve(cmd->path, cmd->args, data->envp);
	error_message(cmd->args[0]);
	ft_exit_exec(126, data, cmd);
	return (0);
}
