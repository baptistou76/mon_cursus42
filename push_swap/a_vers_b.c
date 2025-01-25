/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_vers_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:32:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 13:33:51 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	definir_cible_a(t_node *a, t_node *b)
{
	t_node	*current_b;
	t_node	*target_node;
	long	best_match_index;

	while (a)
	{
		best_match_index = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->num < a->num && current_b->num > best_match_index)
			{
				best_match_index = current_b->num;
				target_node = current_b;
			}
			current_b = current_b->suivant;
		}
		if (best_match_index == LONG_MIN)
			a->cible = plus_gros(b);
		else
			a->cible = target_node;
		a = a->suivant;
	}
}

void	definir_cout_a(t_node *a, t_node *b)
{
	int	len_a;
	int	len_b;

	len_a = taille_pile(a);
	len_b = taille_pile(b);
	while (a)
	{
		a->cout = a->position;
		if (!(a->above_median))
			a->cout = len_a - (a->position);
		if (a->cible->above_median)
			a->cout += a->cible->position;
		else
			a->cout += len_b - (a->cible->position);
		a = a->suivant;
	}
}
