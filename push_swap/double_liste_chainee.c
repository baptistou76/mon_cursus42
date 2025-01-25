/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_liste_chainee.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:39:14 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 14:52:34 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*add_to_empty(int number)
{
	t_node	*temp;

	temp = malloc(sizeof(t_node));
	if (temp == NULL)
		return (NULL);
	temp->precedent = NULL;
	temp->num = number;
	temp->suivant = NULL;
	return (temp);
}

t_node	*add_at_start(t_node *head, int number)
{
	t_node	*new_ptr;

	new_ptr = add_to_empty(number);
	if (new_ptr == NULL)
		return (NULL);
	else
	{
		new_ptr->suivant = head;
		if (head != NULL)
			head->precedent = new_ptr;
		return (new_ptr);
	}
}

t_node	*add_at_end(t_node *head, int number)
{
	t_node	*new_ptr;
	t_node	*last;

	new_ptr = add_to_empty(number);
	if (new_ptr == NULL)
		return (NULL);
	else
	{
		if (head == NULL)
			return (new_ptr);
		last = head;
		while (last->suivant != NULL)
			last = last->suivant;
		last->suivant = new_ptr;
		new_ptr->precedent = last;
		return (head);
	}
}

void	init_dll(int argc, char **argv, t_node **head, int start)
{
	long	temp;
	int		i;

	i = start;
	while (i < argc)
	{
		temp = ft_atol(argv[i]);
		verifs_globales(argv[i], *head, temp);
		if (*head == NULL)
			*head = add_to_empty(temp);
		else
		{
			*head = add_at_end(*head, temp);
			if (*head == NULL)
				return ;
		}
		i++;
	}
}
