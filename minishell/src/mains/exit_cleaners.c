/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleaners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:34:53 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:28:35 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_clean(t_data *data)
{
	ft_putstr_fd("Error: invalid command or arguments\n", 2);
	free_cmd_list(data);
	free_data(data);
	exit(1);
}

void	exit_clean2(t_data *data, t_cmd *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd && cmd->args && cmd->args[0])
		ft_putstr_fd(cmd->args[0], 2);
	else
		ft_putstr_fd("(null)", 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_cmd_list(data);
	free_data(data);
	exit(127);
}

void	ft_exit_exec(int code, t_data *data, t_cmd *cmd)
{
	if (cmd && cmd->path)
		free(cmd->path);
	if (data)
	{
		free_cmd_list(data);
		free_data(data);
	}
	exit(code);
}

void	exit_d(t_data *data)
{
	if (!data->input)
	{
		ft_printf(RED "exit\n" RESET);
		free_cmd_list(data);
		free_data(data);
		exit(0);
	}
}

void	exit_failed_resolution(t_data *data, t_cmd *cmd, int prev_fd)
{
	ft_putstr_fd(RED "minishell: " RESET, 2);
	if (cmd && cmd->args && cmd->args[0])
		ft_putstr_fd(cmd->args[0], 2);
	else
		ft_putstr_fd(RED "(null)" RESET, 2);
	ft_putstr_fd(RED ": command not found\n" RESET, 2);
	safe_close(cmd->pipe_fd[READ]);
	safe_close(cmd->pipe_fd[WRITE]);
	safe_close(prev_fd);
	ft_exit_exec(127, data, cmd);
}
