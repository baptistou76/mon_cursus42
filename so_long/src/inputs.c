/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:21:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 17:55:47 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_inputs(int keysym, t_game *game)
{
	if (keysym == KEY_UP || keysym == KEY_W)
		player_move(game, game->map.player.y - 1, game->map.player.x, BACK);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		player_move(game, game->map.player.y, game->map.player.x - 1, LEFT);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		player_move(game, game->map.player.y, game->map.player.x + 1, RIGHT);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		player_move(game, game->map.player.y + 1, game->map.player.x, FRONT);
	if (keysym == KEY_Q || keysym == KEY_ESC)
		close_game(game);
	return (0);
}

int	can_move_to(t_game *game, int y, int x)
{
	if (game->map.entire[y][x] == FLOOR || game->map.entire[y][x] == COIN
		|| game->map.entire[y][x] == EXIT)
		return (1);
	return (0);
}

void	handle_coin(t_game *game, char *under_player)
{
	if (*under_player == COIN)
	{
		game->map.coins--;
		*under_player = FLOOR;
	}
}

void	update_position(t_game *game, int new_y, int new_x, char *under_player)
{
	int	last_x;
	int	last_y;

	last_x = game->map.player.x;
	last_y = game->map.player.y;
	game->map.entire[last_y][last_x] = *under_player;
	*under_player = game->map.entire[new_y][new_x];
	handle_coin(game, under_player);
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->map.entire[new_y][new_x] = PLAYER;
	game->movements++;
	render_map(game);
}

void	player_move(t_game *game, int new_y, int new_x, int player_sprite)
{
	static char	under_player = FLOOR;

	game->player_sprite = player_sprite;
	if (game->map.entire[new_y][new_x] == EXIT && game->map.coins == 0)
		victory(game);
	if (can_move_to(game, new_y, new_x))
		update_position(game, new_y, new_x, &under_player);
}
