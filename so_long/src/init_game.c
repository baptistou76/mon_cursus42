/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:44:50 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 19:43:13 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_variables(t_game *game)
{
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.players = 0;
	game->movements = 0;
	game->map.columns = ft_strlen(game->map.entire[0]);
	game->player_sprite = RIGHT;
}

void	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
	{
		free(game->mlx_ptr);
		ft_error("Couldn't find mlx pointer\n", game);
	}
	game->mlx_win = mlx_new_window(game->mlx_ptr, game->map.columns * 64,
			game->map.rows * 64, "so_long");
	if (game->mlx_win == NULL)
	{
		free(game->mlx_ptr);
		ft_error("Couldn't create the window.\n", game);
	}
}

void	init_sprites(t_game *game)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	game->wall = new_sprite(mlx, WALL_XPM, game);
	game->floor = new_sprite(mlx, FLOOR_XPM, game);
	game->open_exit = new_sprite(mlx, EXIT_XPM, game);
	game->closed_exit = new_sprite(mlx, FLOOR_XPM, game);
	game->coins = new_sprite(mlx, COIN_XPM, game);
	game->player_right = new_sprite(mlx, PLAYER_R_XPM, game);
	game->player_left = new_sprite(mlx, PLAYER_L_XPM, game);
}

t_imgs	new_sprite(void *mlx, char *path, t_game *game)
{
	t_imgs	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);
	if (sprite.xpm_ptr == NULL)
		ft_error("Couldn't find a sprite.\n", game);
	return (sprite);
}

void	check_for_empty_line(char *map, t_game *game)
{
	if (!map || map[0] == '\0')
	{
		free(map);
		ft_error("Error: Map or file is missing\n", game);
	}
	check_empty_start(map, game);
	check_empty_end(map, game);
	check_empty_middle(map, game);
}
