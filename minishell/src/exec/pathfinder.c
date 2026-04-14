/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:09:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 19:06:55 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*try_paths(char **paths, char *cmd)
{
	int		i;
	char	*res;
	char	*resfinal;

	i = 0;
	while (paths[i])
	{
		res = ft_strjoin(paths[i], "/");
		if (!res)
			return (NULL);
		resfinal = ft_strjoin(res, cmd);
		free(res);
		if (!resfinal)
		{
			free_split(paths);
			return (NULL);
		}
		if (access(resfinal, X_OK) != -1)
			return (free_split(paths), resfinal);
		free(resfinal);
		i++;
	}
	return (free_split(paths), NULL);
}

char	*find_cmd_path(char *cmd, t_data *data)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) != -1)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_env = ft_get_env("PATH", data);
	if (!path_env)
		return (ft_strdup(cmd));
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	cmd_path = try_paths(paths, cmd);
	if (!cmd_path)
		return (ft_strdup(cmd));
	return (cmd_path);
}

char	*get_cmd_path(t_data *data, char **cmd)
{
	return (find_cmd_path(cmd[0], data));
}

void	is_not_path(t_data *data, char **args, char *path)
{
	if (access(data->token->value, F_OK) == 0)
	{
		if (access(data->token->value, X_OK) != 0)
		{
			print_cmd_error(args[0]);
			free_and_exit(data, path, 127);
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_and_exit(data, path, 126);
	}
	print_cmd_error(args[0]);
	free_and_exit(data, path, 127);
}

int	resolve_command_path(t_data *data, t_cmd *cmd)
{
	if (cmd->args && cmd->args[0] && !is_builtin(cmd->args[0])
		&& cmd->args[0][0] != '.' && cmd->args[0][0] != '/')
	{
		cmd->path = find_cmd_path(cmd->args[0], data);
		if (!cmd->path)
		{
			if (cmd && cmd->args && cmd->args[0])
				ft_putstr_fd(cmd->args[0], 2);
			else
				ft_putstr_fd("(null)", 2);
			ft_putstr_fd(": command not found\n", 2);
			return (127);
		}
	}
	return (0);
}
