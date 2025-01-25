/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_turc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:04:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 16:22:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_nodes_a(t_node *a, t_node *b)
{
	definir_position(a);
	definir_position(b);
	definir_cible_a(a, b);
	definir_cout_a(a, b);
	definir_chaepest(a);
}

static void	init_nodes_b(t_node *a, t_node *b)
{
	definir_position(a);
	definir_position(b);
	definir_cible_b(a, b);
}

static void	a_vers_b(t_node **a, t_node **b)
{
	t_node	*cheapest;

	cheapest = return_cheapest(*a);
	if (!cheapest)
		return ;
	if (!cheapest->cible)
		return ;
	if (cheapest->above_median && cheapest->cible->above_median)
		rotate_both(a, b, cheapest);
	else if (!cheapest->above_median && !cheapest->cible->above_median)
		rev_rotate_both(a, b, cheapest);
	prep_for_push(a, cheapest, 'a');
	prep_for_push(b, cheapest->cible, 'b');
	pb(a, b);
}

static void	b_vers_a(t_node **a, t_node **b)
{
	prep_for_push(a, ((*b)->cible), 'a');
	pa(a, b);
}

/* Algorithme principal de mon programme */
void	algo_turc(t_node **a, t_node **b)
{
	int	len_a;

	len_a = taille_pile(*a);
	if (len_a-- > 3 && !pile_triee(*a))
		pb(a, b);
	if (len_a-- > 3 && !pile_triee(*a))
		pb(a, b);
	while (len_a-- > 3 && !pile_triee(*a))
	{
		init_nodes_a(*a, *b);
		a_vers_b(a, b);
	}
	algo_3(a);
	while (*b)
	{
		init_nodes_b(*a, *b);
		b_vers_a(a, b);
	}
	definir_position(*a);
	smallest_on_top(a);
}
