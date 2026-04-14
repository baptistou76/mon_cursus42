/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:20:40 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 14:37:55 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_pwd_env(t_data *data)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_putstr_fd("pwd failed\n", 2), 1);
	ft_replace_in_env(data, "PWD", cwd);
	return (0);
}

int	update_oldpwd_and_chdir(t_data *data, char *path)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_putstr_fd("pwd failed\n", 2), 1);
	ft_replace_in_env(data, "OLDPWD", cwd);
	if (chdir(path) == -1)
		return (1);
	return (0);
}

int	cd_to_home(t_data *data)
{
	char	*home;

	home = ft_get_env("HOME", data);
	if (!home)
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	if (update_oldpwd_and_chdir(data, home))
		return (free(home), 1);
	free(home);
	return (0);
}

int	cd_to_path(t_data *data, char *path)
{
	if (update_oldpwd_and_chdir(data, path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (path)
			ft_putstr_fd(path, 2);
		else
			ft_putstr_fd("(null)", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_list;
	if (!cmd->args[1])
	{
		if (cd_to_home(data))
			return (1);
	}
	else if (cmd->args[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	else
	{
		if (cd_to_path(data, cmd->args[1]))
			return (1);
	}
	return (update_pwd_env(data));
}
