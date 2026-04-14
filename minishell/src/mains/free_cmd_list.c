/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:32:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:05:43 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_list(t_data *data)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!data || !data->cmd_list)
		return ;
	current = data->cmd_list;
	while (current)
	{
		next = current->next;
		if (current->outfile)
			free_redir_list(current->outfile);
		if (current->infile)
			free_redir_list(current->infile);
		if (current->args)
			free_split(current->args);
		free(current);
		current = next;
	}
	data->cmd_list = NULL;
}

void	free_cmd_list2(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		if (current->outfile)
			free_redir_list(current->outfile);
		if (current->infile)
			free_redir_list(current->infile);
		if (current->args)
			free_split(current->args);
		free(current);
		current = next;
	}
}
