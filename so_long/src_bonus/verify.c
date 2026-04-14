/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:49:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 10:28:57 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	map_checker(t_game *game)
{
	rows_checker(game);
	columns_checker(game);
	params_counter(game);
	params_map_checker(game);
	check_path_to_exit(game);
}

void	rows_checker(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.entire[i][0] != WALL)
			ft_error("Invalid map: Wall missing on first row\n", game);
		else if (game->map.entire[i][game->map.columns - 1] != WALL)
			ft_error("Invalid map: Wall missing on last row\n", game);
		i++;
	}
}

void	columns_checker(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.entire[0][i] != WALL)
			ft_error("Invalid map: Wall missing on first columns\n", game);
		else if (game->map.entire[game->map.rows - 1][i] != WALL)
			ft_error("Invalid map: Wall missing on last columns\n", game);
		i++;
	}
}

void	params_counter(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			if (!ft_strchr("CE0P1Zz", game->map.entire[y][x]))
				ft_error("Invalid map: Not expected map parameters\n", game);
			else if (game->map.entire[y][x] == PLAYER)
			{
				game->map.players++;
				game->map.player.x = x;
				game->map.player.y = y;
			}
			else if (game->map.entire[y][x] == COIN)
				game->map.coins++;
			else if (game->map.entire[y][x] == EXIT)
				game->map.exit++;
			x++;
		}
		y++;
	}
}

void	params_map_checker(t_game *game)
{
	if (game->map.coins == 0)
		ft_error("Invalid map: No collectibles find\n", game);
	else if (game->map.exit == 0)
		ft_error("Invalid map: No exit found\n", game);
	else if (game->map.players != 1)
		ft_error("Invalid game: You need one and only one hero\n", game);
}
