/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:29:01 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 17:55:59 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			identify_sprite(game, y, x);
			x++;
		}
		y++;
	}
	print_movements(game);
	return (0);
}

void	identify_sprite(t_game *game, int y, int x)
{
	char	params;

	params = game->map.entire[y][x];
	if (params == WALL)
		render_sprite(game, game->wall, y, x);
	else if (params == FLOOR)
		render_sprite(game, game->floor, y, x);
	else if (params == COIN)
		render_sprite(game, game->coins, y, x);
	else if (params == EXIT)
	{
		if (game->map.coins == 0)
			render_sprite(game, game->open_exit, y, x);
		else
			render_sprite(game, game->closed_exit, y, x);
	}
	else if (params == PLAYER)
		render_player(game, y, x);
}

void	render_player(t_game *game, int y, int x)
{
	if (game->player_sprite == FRONT)
		render_sprite(game, game->player_right, y, x);
	if (game->player_sprite == LEFT)
		render_sprite(game, game->player_left, y, x);
	if (game->player_sprite == RIGHT)
		render_sprite(game, game->player_right, y, x);
	if (game->player_sprite == BACK)
		render_sprite(game, game->player_right, y, x);
}

void	render_sprite(t_game *game, t_imgs sprite, int line, int columns)
{
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, sprite.xpm_ptr,
		columns * sprite.x, line * sprite.y);
}

void	print_movements(t_game *game)
{
	ft_dprintf(2, "Movement: %d\n", game->movements);
}
