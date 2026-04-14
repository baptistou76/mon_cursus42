/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:52:51 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/19 17:40:00 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Va gerer les processus en faisant des pipes et des fork */
void	process_pipeline(t_pipex *head)
{
	t_pipex	*node;

	node = head;
	while (node)
	{
		do_pipe(node);
		node->pid = secure_fork();
		if (node->pid == 0)
		{
			exec(node);
			exit(EXIT_SUCCESS);
		}
		else
			close_pipes(node);
		node = node->next;
	}
	node = head;
	while (node)
	{
		waitpid(node->pid, NULL, 0);
		node = node->next;
	}
}

/* Va creer un pipe et rediriger le fd en fonction de la position du noeud */
void	do_pipe(t_pipex *node)
{
	if (!node || node->is_last)
		return ;
	if (pipe(node->pipefd) == -1)
		ft_perror("Pipe failed");
}

/* Va close les pipefd celon le besoin de la condition */
void	close_pipes(t_pipex *node)
{
	if (!node->is_first && node->prev && node->prev->pipefd[0] != -1)
		secure_close(node->prev->pipefd[0]);
	if (!node->is_last && node->pipefd[1] != -1)
		secure_close(node->pipefd[1]);
}
