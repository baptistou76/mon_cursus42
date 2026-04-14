/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:41:47 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 09:42:37 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_child_process(t_data *data, t_cmd *cmd, int prev_fd)
{
	char	**args;
	char	*path;

	reset_signals_child();
	signal(SIGPIPE, SIG_IGN);
	init_exec_vars(cmd, &args, &path, data);
	if (redirect_management(cmd, prev_fd) == -1)
		return (CODE_FAIL);
	return (handle_exec(data, cmd, args, path));
}

int	handle_exec(t_data *data, t_cmd *cmd, char **args, char *path)
{
	close_fds(cmd);
	if (!path)
	{
		print_no_such_file(path, args);
		free_and_exit(data, path, 127);
	}
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		free_and_exit(data, path, 0);
	return (check_path_and_exec(data, args, path));
}

int	check_path_and_exec(t_data *data, char **args, char *path)
{
	if (is_directory(path))
	{
		is_a_directory(args[0]);
		free_and_exit(data, path, 126);
	}
	if (path[0] != '/')
		is_not_path(data, args, path);
	execve(path, args, data->envp);
	print_no_such_file(path, args);
	free_and_exit(data, path, 127);
	return (127);
}
