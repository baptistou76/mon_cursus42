/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:10:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 13:27:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	definir_position(t_node *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = taille_pile(stack) / 2;
	while (stack)
	{
		stack->position = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->suivant;
		++i;
	}
}

void	definir_chaepest(t_node *stack)
{
	long	chpst;
	t_node	*cheapest_node;

	if (!stack)
		return ;
	chpst = LONG_MAX;
	while (stack)
	{
		if (stack->cout < chpst)
		{
			chpst = stack->cout;
			cheapest_node = stack;
		}
		stack = stack->suivant;
	}
	cheapest_node->cheapest = true;
}

void	prep_for_push(t_node **stack, t_node *top_node, char stack_name)
{
	if (!stack || !top_node)
		return ;
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
			{
				ra(stack);
			}
			else
			{
				rra(stack);
			}
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}

void	smallest_on_top(t_node **a)
{
	while ((*a)->num != plus_petit(*a)->num)
	{
		if (plus_petit(*a)->above_median)
			ra(a);
		else
			rra(a);
	}
}
