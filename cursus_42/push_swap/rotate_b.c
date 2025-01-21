/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:49:45 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/20 17:34:19 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rb(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	last = stack->top;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	if (a->size > 1)
		ra(a);
	if (b->size > 1)
		rb(b);
	write(1, "rr\n", 3);
}

void	rrb(t_stack *stack)
{
	t_node	*last;
	t_node	*prev;

	if (stack->size < 2)
		return ;
	last = stack->top;
	prev = NULL;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = stack->top;
	stack->top = last;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b)
{
	if (a->size > 1)
		rra(a);
	if (b->size > 1)
		rrb(b);
	write(1, "rrr\n", 4);
}
