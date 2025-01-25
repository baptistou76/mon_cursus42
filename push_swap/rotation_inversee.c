/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_inversee.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:00:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 15:21:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_node **stack)
{
	t_node	*last;
	t_node	*second_last;

	if (!*stack || !(*stack)->suivant)
		return ;
	last = *stack;
	while (last->suivant)
	{
		second_last = last;
		last = last->suivant;
	}
	second_last->suivant = NULL;
	last->suivant = *stack;
	last->precedent = NULL;
	(*stack)->precedent = last;
	*stack = last;
}

void	rra(t_node **stack_a)
{
	reverse_rotate(stack_a);
	ft_printf("rra\n");
}

void	rrb(t_node **stack_b)
{
	reverse_rotate(stack_b);
	ft_printf("rrb\n");
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	ft_printf("rrr\n");
}

void	rev_rotate_both(t_node **a, t_node **b, t_node *cheapest)
{
	while (*b != cheapest->cible && *a != cheapest)
		rrr(a, b);
	definir_position(*a);
	definir_position(*b);
}
