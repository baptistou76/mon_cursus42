/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:27:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:40:29 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_process(t_data *data, t_cmd *cmd, int prev_fd)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), CODE_FAIL);
	if (pid == 0)
	{
		ret = resolve_command_path(data, cmd);
		if (ret != 0)
			exit_failed_resolution(data, cmd, prev_fd);
		exec_child(data, cmd, prev_fd);
	}
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	return (pid);
}

int	ft_executables(t_data *data, t_cmd *cmd, int input_fd, int output_fd)
{
	struct stat	stat_info;
	int			status;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 127);
	if (pid == 0)
	{
		exec_redirection(data, cmd, input_fd, output_fd);
		if (stat(cmd->args[0], &stat_info) == 0)
		{
			if (S_ISDIR(stat_info.st_mode))
			{
				is_a_directory(cmd->args[0]);
				free_cmd_list(data);
				free_data(data);
				exit(126);
			}
		}
		execve(cmd->args[0], cmd->args, data->envp);
		exit_clean2(data, cmd);
	}
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}
