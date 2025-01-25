/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chercheurs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:47:05 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 13:26:18 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*plus_gros(t_node *stack)
{
	long	biggest;
	t_node	*biggest_node;

	if (!stack)
		return (NULL);
	biggest = LONG_MIN;
	while (stack)
	{
		if (stack->num > biggest)
		{
			biggest = stack->num;
			biggest_node = stack;
		}
		stack = stack->suivant;
	}
	return (biggest_node);
}

t_node	*plus_petit(t_node *stack)
{
	long	smallest;
	t_node	*smallest_node;

	if (!stack)
		return (NULL);
	smallest = LONG_MAX;
	while (stack)
	{
		if (stack->num < smallest)
		{
			smallest = stack->num;
			smallest_node = stack;
		}
		stack = stack->suivant;
	}
	return (smallest_node);
}

t_node	*dernier_noeud(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->suivant)
		stack = stack->suivant;
	return (stack);
}

int	taille_pile(t_node *stack)
{
	int	count;

	if (!stack)
		return (0);
	count = 0;
	while (stack)
	{
		stack = stack->suivant;
		count++;
	}
	return (count);
}

t_node	*return_cheapest(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->suivant;
	}
	return (NULL);
}
