/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:28:57 by broboeuf          #+#    #+#             */
/*   Updated: 2025/06/14 09:26:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exec_vars(t_cmd *cmd, char ***args, char **path, t_data *data)
{
	*args = cmd->args;
	*path = get_cmd_path(data, *args);
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->saved_stdin != STDIN_FILENO)
		close(cmd->saved_stdin);
	if (cmd->saved_stdout != STDOUT_FILENO)
		close(cmd->saved_stdout);
}

void	print_no_such_file(char *path, char **args)
{
	ft_putstr_fd("minishell: ", 2);
	if (path)
		ft_putstr_fd(path, 2);
	else if (args && args[0])
		ft_putstr_fd(args[0], 2);
	else
		ft_putstr_fd("(null)", 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	free_and_exit(t_data *data, char *path, int code)
{
	if (data->cmd_list)
		free_cmd_list(data);
	if (data)
		free_data(data);
	if (path)
		free(path);
	exit(code);
}

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}
