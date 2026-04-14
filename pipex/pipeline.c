/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:04:08 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/19 11:09:09 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Initialise la structure du pipeline */
t_pipex	*init_pipeline(t_data *data)
{
	t_pipex	*head;
	t_pipex	*current;
	t_pipex	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	if (data->bonus)
		i = 3;
	else
		i = 2;
	while (i < data->ac - 1)
	{
		data->prev = current;
		data->cmd = data->av[i];
		new_node = add_pipex_node(data);
		if (!new_node)
			return (NULL);
		current = new_node;
		if (!head)
			head = current;
		i++;
	}
	set_first_or_last(head);
	return (head);
}

/* Va ajouter le noeud a la dll pipex */
t_pipex	*add_pipex_node(t_data *data)
{
	t_pipex	*new_node;

	new_node = create_node(data);
	if (!new_node)
		return (NULL);
	if (data->prev)
	{
		data->prev->next = new_node;
		new_node->prev = data->prev;
	}
	return (new_node);
}

/* Va determiner si le noeud est le premier, le dernier ou au milieu */
void	set_first_or_last(t_pipex *head)
{
	if (head == NULL)
		return ;
	while (head)
	{
		if (head->next == NULL)
			head->is_last = true;
		if (head->prev == NULL)
			head->is_first = true;
		if (head->prev && head->next)
			head->is_middle = true;
		head = head->next;
	}
}
