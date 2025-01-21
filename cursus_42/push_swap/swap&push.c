/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap&push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:09:14 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/20 10:50:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack->top = second;
	write(1, "sa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
	int	value;

	if (a->size > 0)
	{
		value = pop(a);
		push(b, value);
		write(1, "pb\n", 3);
	}
}

void	sb(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack->top = second;
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	sa(a);
	sb(b);
	write(1, "ss\n", 3);
}

void	pa(t_stack *a, t_stack *b)
{
	int	value;

	if (b->size > 0)
	{
		value = pop(b);
		push(a, value);
		write(1, "pa\n", 3);
	}
}
