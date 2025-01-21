/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:39:50 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/20 17:40:05 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack_a;
	t_stack	stack_b;

	if (argc < 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	stack_a.top = NULL;
	stack_a.size = 0;
	stack_b.top = NULL;
	stack_b.size = 0;
	if (!parse_args(&stack_a, argv + 1))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	// Test des commandes
	sa(&stack_a);
	pb(&stack_a, &stack_b);
	pa(&stack_a, &stack_b);
	ra(&stack_a);
	rra(&stack_a);
	rb(&stack_b);
	rrb(&stack_b);
	rr(&stack_a, &stack_b);
	rrr(&stack_a, &stack_b);
	// Libération de la mémoire
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
