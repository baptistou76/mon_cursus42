/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:24:56 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/21 12:48:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Fonction qui va executer les commandes avec le bon PATH */
void	exec(t_pipex *node)
{
	char	*path;

	exec_redirection(node);
	path = get_path(node);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		ft_free_pipeline(node);
		exit(EXIT_FAILURE);
	}
	else
	{
		execve(path, node->args, node->envp);
		ft_putstr_fd("Execve failed", 2);
		ft_putendl_fd(node->args[0], 2);
		free(path);
		ft_free_pipeline(node);
		exit(EXIT_FAILURE);
	}
}

/* Va determiner l'ordre des pipefd et le here_doc, au cas ou... */
void	exec_redirection_first(t_pipex *node)
{
	if (node->is_here_doc)
	{
		here_doc_redirection(node);
	}
	else
	{
		if (!node->infile)
			error_and_exit(node, "Invalid infile");
		node->input = secure_open(node->infile, O_RDONLY);
		if (node->input == -1)
			error_and_exit(node, "Open failed");
		secure_dup2(node->input, STDIN_FILENO);
		secure_close(node->input);
		secure_dup2(node->pipefd[1], STDOUT_FILENO);
		secure_close(node->pipefd[1]);
		secure_close(node->pipefd[0]);
	}
}

/* Va determiner dans quel ordre  les pipefd seront ouverts et fermes */
void	exec_redirection(t_pipex *node)
{
	if (node->is_first)
		exec_redirection_first(node);
	if (node->is_middle)
	{
		secure_dup2(node->prev->pipefd[0], STDIN_FILENO);
		secure_close(node->prev->pipefd[0]);
		secure_dup2(node->pipefd[1], STDOUT_FILENO);
		secure_close(node->pipefd[1]);
		secure_close(node->pipefd[0]);
	}
	if (node->is_last)
	{
		last_node_redirection(node);
	}
}

void	here_doc_redirection(t_pipex *node)
{
	if (!node->infile)
		error_and_exit(node, "Invalide here_doc");
	node->input = secure_open(node->infile, O_RDONLY);
	if (node->input == -1)
		error_and_exit(node, "Open failed");
	secure_dup2(node->input, STDIN_FILENO);
	secure_close(node->input);
	secure_dup2(node->pipefd[1], STDOUT_FILENO);
	secure_close(node->pipefd[1]);
	secure_close(node->pipefd[0]);
}

void	last_node_redirection(t_pipex *node)
{
	if (!node->outfile)
		ft_perror("Invalid output");
	node->output = secure_open(node->outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if (node->output == -1)
	{
		if (node->prev)
			secure_close(node->prev->pipefd[0]);
		error_and_exit(node, "Open failed");
	}
	secure_dup2(node->prev->pipefd[0], STDIN_FILENO);
	secure_close(node->prev->pipefd[0]);
	secure_dup2(node->output, STDOUT_FILENO);
	secure_close(node->output);
}
