/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erreurs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:42:49 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 15:19:23 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	error_syntax(char *s)
{
	if (!(*s == '+' || *s == '-' || (ft_isdigit(*s))))
		return (1);
	if ((*s == '+' || *s == '-') && !(ft_isdigit(s[1])))
		return (1);
	while (*++s)
	{
		if (!(ft_isdigit(*s)))
			return (1);
	}
	return (0);
}

static int	error_duplicate(t_node *a, int n)
{
	if (!a)
		return (0);
	while (a)
	{
		if (a->num == n)
			return (1);
		a = a->suivant;
	}
	return (0);
}

void	free_stack(t_node **stack)
{
	t_node	*tmp;
	t_node	*current;

	if (!*stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->suivant;
		current->num = 0;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void	verifs_globales(char *s, t_node *a, long n)
{
	if (n < LONG_MIN || n > LONG_MAX)
		free_erreurs(&a);
	if (error_syntax(s) != 0)
		free_erreurs(&a);
	if (error_duplicate(a, n) != 0)
		free_erreurs(&a);
}

void	free_erreurs(t_node **a)
{
	free_stack(a);
	ft_printf("Error\n");
	exit(1);
}
