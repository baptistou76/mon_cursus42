/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:50:17 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 15:39:30 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Va determiner la taille du tableau apres split */
static size_t	taille_tab(char **tab)
{
	size_t	len;

	len = 0;
	while (tab[len] != NULL)
		len++;
	return (len);
}

/* Va liberer la memoire du tableau */
static void	free_str_tab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

/* Va init split pour transformer argv en tab */
static void	init_split(int argc, char **argv, t_node **stack)
{
	argv = ft_split(argv[1], ' ');
	argc = taille_tab(argv);
	init_dll(argc, argv, stack, 0);
	free_str_tab(argv);
}

/* Va selectionner l'alogo a utiliser*/
static void	algo_selecteur(t_node **stack_a, t_node **stack_b)
{
	if (taille_pile(*stack_a) == 2)
		sa(stack_a);
	else if (taille_pile(*stack_a) == 3)
		algo_3(stack_a);
	else
		algo_turc(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 2)
		init_split(argc, argv, &stack_a);
	else if (argc > 2)
		init_dll(argc, argv, &stack_a, 1);
	else
		return (1);
	if (!pile_triee(stack_a))
		algo_selecteur(&stack_a, &stack_b);
	free_stack(&stack_a);
	return (0);
}
