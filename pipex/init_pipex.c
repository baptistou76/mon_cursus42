/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:01:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/19 19:46:16 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Va gerer les erreurs de split pour les args */
// static void	handle_node_error(t_pipex *node)
// {
// 	free(node->cmd);
// 	ft_free_split(node->args);
// 	free(node);
// }

/* Va initialiser le nouveau noeud avec les valeurs par defaut */
static void	init_node(t_pipex *node, t_data *data)
{
	node->outfile = data->av[data->ac - 1];
	node->infile = data->av[1];
	node->envp = NULL;
	if (data->bonus)
	{
		node->is_here_doc = true;
		node->here_doc = data->av[2];
	}
	else
	{
		node->is_here_doc = false;
		node->here_doc = NULL;
	}
	node->input = -1;
	node->output = -1;
	node->pipefd[0] = -1;
	node->pipefd[1] = -1;
	node->prev = NULL;
	node->next = NULL;
	node->pid = -1;
	node->is_last = false;
	node->is_middle = false;
	node->is_first = false;
}

/* Creation du nouveau noeud dans la struct pipex */
t_pipex	*create_node(t_data *data)
{
	t_pipex	*node;

	node = malloc(sizeof(t_pipex));
	if (!node)
		return (NULL);
	init_node(node, data);
	node->cmd = ft_strdup(data->cmd);
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	node->args = args_split(node->cmd);
	if (!node->args)
	{
		free(node->cmd);
		free(node);
		return (NULL);
	}
	node->envp = data->envp;
	return (node);
}
