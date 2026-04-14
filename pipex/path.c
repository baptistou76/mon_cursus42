/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:31:16 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/21 12:38:35 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Va servir a recuperer le chemin de l'envp */
char	*get_envp(char *name, t_pipex *node)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (node->envp[i])
	{
		j = 0;
		while (node->envp[i][j] && node->envp[i][j] != '=')
			j++;
		sub = ft_substr(node->envp[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (node->envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

/* Va verifier si la cmd est passee en chemin absolue */
char	*check_absolute_path(t_pipex *node)
{
	if (node->args[0][0] == '/')
	{
		if (access(node->args[0], F_OK | X_OK) == 0)
		{
			return (node->args[0]);
		}
		return (NULL);
	}
	return (NULL);
}

/* Va verifier si la cmd est dans le repertoire courant */
char	*check_current_directory(t_pipex *node)
{
	if (access(node->args[0], F_OK | X_OK) == 0)
	{
		return (node->args[0]);
	}
	return (NULL);
}

/* Va chercher la cmd en parcourant le chemin d'acces */
char	*search_in_path(t_pipex *node, char **all_path)
{
	int		i;
	char	*exec;
	char	*path_part;

	i = 0;
	while (all_path[i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		if (!path_part)
			return (NULL);
		exec = ft_strjoin(path_part, node->args[0]);
		free(path_part);
		if (!exec)
			return (NULL);
		if (access(exec, F_OK | X_OK) == 0)
		{
			return (exec);
		}
		free(exec);
		i++;
	}
	return (NULL);
}

/* Va checker si la cmd est en chemin absolue ou non et l'envoyer a l'exec */
char	*get_path(t_pipex *node)
{
	char	*exec;
	char	**all_path;

	exec = check_absolute_path(node);
	if (exec)
		return (exec);
	all_path = ft_split(get_envp("PATH", node), ':');
	if (!all_path)
	{
		exec = check_current_directory(node);
		return (exec);
	}
	exec = search_in_path(node, all_path);
	ft_free_split(all_path);
	return (exec);
}
