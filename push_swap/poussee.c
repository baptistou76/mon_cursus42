/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poussee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:59:31 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 15:22:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_node **dest, t_node **source)
{
	t_node	*to_push;

	if (!*source)
		return ;
	to_push = *source;
	*source = (*source)->suivant;
	if (*source)
		(*source)->precedent = NULL;
	to_push->precedent = NULL;
	if (!*dest)
	{
		*dest = to_push;
		to_push->suivant = NULL;
	}
	else
	{
		to_push->suivant = *dest;
		to_push->suivant->precedent = to_push;
		*dest = to_push;
	}
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	push(stack_b, stack_a);
	ft_printf("pb\n");
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	push(stack_a, stack_b);
	ft_printf("pa\n");
}
