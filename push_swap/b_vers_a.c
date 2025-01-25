/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_vers_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:35:56 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 13:33:22 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	definir_cible_b(t_node *a, t_node *b)
{
	t_node	*current_a;
	t_node	*target_node;
	long	best_match;

	while (b)
	{
		best_match = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->num > b->num && current_a->num < best_match)
			{
				best_match = current_a->num;
				target_node = current_a;
			}
			current_a = current_a->suivant;
		}
		if (best_match == LONG_MAX)
			b->cible = plus_petit(a);
		else
			b->cible = target_node;
		b = b->suivant;
	}
}
