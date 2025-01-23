/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:53:57 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/23 18:54:13 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Loop decays once
 * 		~cheapest_node tops is a
 * 		~relative target_node tops in b
 */

/*
 * Conclude the rotation of the stacks
 */
void	finish_rotation(t_stack_node **stack, t_stack_node *top_node,
		char stack_name)
{
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}
	}
}

/*
 * Move the node from 'b' to 'a'
 * with the metadata available in the node
 * 1)Make the target nodes emerge
 * 2)push in A
 */
void	move_nodes(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest_node;

	cheapest_node = return_cheapest(*b);
	if (cheapest_node->above_median && cheapest_node->target_node->above_median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median)
		&& !(cheapest_node->target_node->above_median))
		rev_rotate_both(a, b, cheapest_node);
	finish_rotation(b, cheapest_node, 'b');
	finish_rotation(a, cheapest_node->target_node, 'a');
	pa(a, b, false);
}

/*
 * ~Push all nodes in B
 * ~For every configuration choose the "cheapest_node"
 * ~Push everything back in A in order
 */
void	push_swap(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*smallest;
	int				len_a;

	len_a = stack_len(*a);
	if (!stack_sorted(*a))
	{
		if (len_a >= 5)
			turk_sort(a, b);
		else
		{
			while (len_a-- > 3)
				pb(b, a, false);
		}
		tiny_sort(a);
	}
	while (*b)
	{
		init_nodes(*a, *b);
		move_nodes(a, b);
	}
	set_current_position(*a);
	smallest = find_smallest(*a);
	if (smallest->above_median)
		while (*a != smallest)
			ra(a, false);
	else
		while (*a != smallest)
			rra(a, false);
}
