/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:41:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:43:40 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_existing_name(t_data *data, char *name, char *content)
{
	t_env	*new_env;

	if (!check_name(name, data->env, content) && content)
	{
		new_env = env_new(name, content);
		ft_lstadd_back_env(&data->env, new_env);
	}
	free(name);
	if (content)
		free(content);
}

int	add_in_export(t_data *data, char *str)
{
	int		i;
	char	*name;
	char	*content;
	t_env	*new_export;
	t_env	*new_env;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	content = get_content(str, i);
	if (check_name(name, data->export, content))
		return (handle_existing_name(data, name, content), 0);
	new_export = env_new(name, content);
	new_env = env_new(name, content);
	if (content)
		ft_lstadd_back_env(&data->env, new_env);
	else
		free_env_list(new_env);
	ft_lstadd_back_env(&data->export, new_export);
	free(name);
	if (content)
		free(content);
	return (0);
}

void	print_export_list(t_env *export)
{
	while (export)
	{
		if (!export->content)
			ft_printf("declare -x %s\n", export->name);
		else
			ft_printf("declare -x %s=\"%s\"\n", export->name, export->content);
		export = export->next;
	}
}

int	export_variable(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!ft_is_valid(cmd->args[i]))
		{
			ft_putstr_fd(RED "export: `" RESET, 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(RED "': not a valid identifier\n" RESET, 2);
			return (1);
		}
		add_in_export(data, cmd->args[i]);
		i++;
	}
	return (0);
}

int	ft_export(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_list;
	if (!cmd->args[1])
	{
		print_export_list(data->export);
		return (0);
	}
	return (export_variable(data, cmd));
}
