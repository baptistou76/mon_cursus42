/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:37:20 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 12:39:00 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	pile_triee(t_node *stack)
{
	if (!stack)
		return (1);
	while (stack->suivant)
	{
		if (stack->num > stack->suivant->num)
			return (false);
		stack = stack->suivant;
	}
	return (true);
}

int	verif_triage(t_node **list)
{
	t_node	*ptr;

	if (*list == NULL)
		return (1);
	ptr = (*list)->suivant;
	while (ptr != *list)
	{
		if (ptr->num > ptr->suivant->num)
			return (0);
		ptr = ptr->suivant;
	}
	return (1);
}
