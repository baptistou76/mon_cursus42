/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:02:18 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 13:34:42 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	algo_3(t_node **a)
{
	t_node	*biggest;

	biggest = plus_gros(*a);
	if (biggest == *a)
		ra(a);
	else if (biggest == (*a)->suivant)
		rra(a);
	if ((*a)->num > (*a)->suivant->num)
		sa(a);
}
