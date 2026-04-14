/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:15:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/07/31 01:45:43 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	on_focus_in(t_game *game)
{
	mlx_mouse_hide(game->mlx, game->win);
	return (0);
}

int	on_focus_out(t_game *game)
{
	mlx_mouse_show(game->mlx, game->win);
	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 9, (1L << 21), on_focus_in, game);
	mlx_hook(game->win, 10, (1L << 3), on_focus_out, game);
	mlx_hook(game->win, 17, (1L << 2), free_game, game);
	mlx_loop_hook(game->mlx, update_game, game);
}

int	handle_focus_in(t_game *game)
{
	game->has_focus = 1;
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	handle_focus_out(t_game *game)
{
	game->has_focus = 0;
	mlx_mouse_show(game->mlx, game->win);
	return (0);
}
