/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:53:17 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/20 14:28:07 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(t_stack *stack, char **argv)
{
	int	i;
	int	value;

	i = 0;
	while (argv[i] != NULL)
	{
		if (!is_valid_number(argv[i]))
			return (0);
		value = ft_atoi(argv[i]);
		push(stack, value);
		i++;
	}
	return (1);
}
