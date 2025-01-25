/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:01:25 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 15:21:02 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_node **stack)
{
	t_node	*last;

	if (!*stack || !(*stack)->suivant)
		return ;
	last = dernier_noeud(*stack);
	last->suivant = *stack;
	*stack = (*stack)->suivant;
	(*stack)->precedent = NULL;
	last->suivant->precedent = last;
	last->suivant->suivant = NULL;
}

void	ra(t_node **stack_a)
{
	rotate(stack_a);
	ft_printf("ra\n");
}

void	rb(t_node **stack_b)
{
	rotate(stack_b);
	ft_printf("rb\n");
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	ft_printf("rr\n");
}

void	rotate_both(t_node **a, t_node **b, t_node *cheapest)
{
	while (*b != cheapest->cible && *a != cheapest)
		rr(a, b);
	definir_position(*a);
	definir_position(*b);
}
