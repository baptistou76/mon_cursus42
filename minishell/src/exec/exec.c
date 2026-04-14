/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:21:14 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:16:00 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_line(t_data *data, t_cmd *cmd)
{
	int		prev_fd;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	if (cmd->next == NULL)
		return (handle_single_command(data, cmd, prev_fd));
	while (cmd)
	{
		if (cmd->next != NULL && pipe(cmd->pipe_fd) == -1)
			return (perror("pipe error"), 1);
		handle_useless_command(cmd, &prev_fd);
		last_pid = ft_process(data, cmd, prev_fd);
		safe_close(cmd->pipe_fd[WRITE]);
		fds_redirection(cmd, &prev_fd);
		cmd = cmd->next;
	}
	return (wait_for_children(data, last_pid, prev_fd));
}

int	exec_direct(t_data *data, t_cmd *cmd, int prev_fd)
{
	if (access(cmd->args[0], F_OK) == -1)
		return (no_such_file_or_directory(cmd->args[0]), 126);
	if (access(cmd->args[0], X_OK) == -1)
		return (permission_denied(cmd->args[0]), 126);
	else
		execve(cmd->args[0], cmd->args, data->envp);
	safe_close(prev_fd);
	safe_close(cmd->pipe_fd[READ]);
	safe_close(cmd->pipe_fd[WRITE]);
	safe_close(prev_fd);
	ft_exit_exec(126, data, cmd);
	return (0);
}

int	exec_shell(t_data *data, t_cmd *cmd, int prev_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 1);
	if (pid == 0)
		exec_child_process(data, cmd, prev_fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFSIGNALED(status))
	{
		data->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		data->last_status = WEXITSTATUS(status);
	return (data->last_status);
}

void	exec_child(t_data *data, t_cmd *cmd, int prev_fd)
{
	int	status;

	reset_signals_child();
	if (redirect_management(cmd, prev_fd) == 1)
		return (safe_close(prev_fd), ft_exit_exec(1, data, cmd));
	if (!cmd || !cmd->args || !cmd->args[0])
		handle_invalid_command(data, cmd, prev_fd);
	handle_invalid_args(data, cmd, prev_fd);
	close_all_fds(prev_fd, cmd->pipe_fd[READ], cmd->pipe_fd[WRITE]);
	if (is_builtin(cmd->args[0]))
	{
		status = run_builtin(data, cmd);
		close_all_fds(prev_fd, cmd->pipe_fd[READ], cmd->pipe_fd[WRITE]);
		ft_exit_exec(status, data, cmd);
	}
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
		exec_direct(data, cmd, prev_fd);
	if (cmd->path)
		handle_path_exec(data, cmd);
	error_message(cmd->args[0]);
	ft_exit_exec(127, data, cmd);
}
