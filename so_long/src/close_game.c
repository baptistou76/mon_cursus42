/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:26:41 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 17:55:14 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	victory(t_game *game)
{
	ft_printf("\nMovements: %d\n", ++game->movements);
	free_allocated_memory(game);
	ft_printf("\nYOU WIN !!!\n\n");
	exit(EXIT_FAILURE);
}

int	close_game(t_game *game)
{
	ft_printf("Movements: %d\n", game->movements);
	free_allocated_memory(game);
	ft_printf("\nCLOSED\n");
	exit(EXIT_FAILURE);
}

int	ft_error(char *msg, t_game *game)
{
	if (game->map_alloc == true)
		ft_free_map(game);
	free(game);
	ft_printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}
