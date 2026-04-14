/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:59:03 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/20 10:41:52 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	error_and_exit(t_pipex *node, char *msg)
{
	perror(msg);
	cleanup(node);
	ft_free_pipeline(node);
	exit(EXIT_FAILURE);
}

/* Va servir a free toute la structure */
void	ft_free_pipeline(t_pipex *head)
{
	t_pipex	*tmp;

	if (!head)
		return ;
	while (head->prev)
		head = head->prev;
	while (head)
	{
		tmp = head->next;
		cleanup_head(head);
		free(head);
		head = tmp;
	}
}

void	cleanup(t_pipex *node)
{
	if (node->input != 1)
		secure_close(node->input);
	if (node->output != -1)
		secure_close(node->output);
	if (node->pipefd[0] != -1)
		secure_close(node->pipefd[0]);
	if (node->pipefd[1] != -1)
		secure_close(node->pipefd[1]);
}

void	cleanup_head(t_pipex *head)
{
	if (head->cmd != NULL)
	{
		free(head->cmd);
		head->cmd = NULL;
	}
	if (head->args != NULL)
	{
		ft_free_split(head->args);
		head->args = NULL;
	}
}
