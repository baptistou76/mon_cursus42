/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:51:25 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/31 03:21:18 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Vérifie si une position est bloquée (mur ou bordure)
 * @param game structure principale du jeu
 * @param x coordonnée x de la position à tester
 * @param y coordonnée y de la position à tester
 * @return 1 si bloqué, 0 sinon
 */
static int	is_position_blocked(t_game *game, int x, int y)
{
	if (is_blocking_up(game, x, y))
		return (1);
	if (is_blocking_down(game, x, y))
		return (1);
	if (is_blocking_right(game, x, y))
		return (1);
	if (is_blocking_left(game, x, y))
		return (1);
	return (0);
}

/**
 * Déplace le joueur vers l'avant avec glissement sur les murs
 */
void	move_player_forward(t_game *game)
{
	double	nx;
	double	ny;
	double	s;

	s = game->player.speed;
	nx = game->player.map_pos.x + cos(game->player.dir) * s;
	ny = game->player.map_pos.y + sin(game->player.dir) * s;
	if (!is_position_blocked(game, nx, game->player.map_pos.y))
		game->player.map_pos.x = nx;
	if (!is_position_blocked(game, game->player.map_pos.x, ny))
		game->player.map_pos.y = ny;
	game->player.pos_x = game->player.map_pos.x;
	game->player.pos_y = game->player.map_pos.y;
	draw_frame(game);
}

/**
 * Déplace le joueur vers l'arrière avec glissement sur les murs
 */
void	move_player_backward(t_game *game)
{
	double	nx;
	double	ny;
	double	s;

	s = game->player.speed;
	nx = game->player.map_pos.x - cos(game->player.dir) * s;
	ny = game->player.map_pos.y - sin(game->player.dir) * s;
	if (!is_position_blocked(game, nx, game->player.map_pos.y))
		game->player.map_pos.x = nx;
	if (!is_position_blocked(game, game->player.map_pos.x, ny))
		game->player.map_pos.y = ny;
	game->player.pos_x = game->player.map_pos.x;
	game->player.pos_y = game->player.map_pos.y;
	draw_frame(game);
}

/**
 * Déplace le joueur vers la gauche (strafe) avec glissement
 */
void	move_player_left(t_game *game)
{
	double	nx;
	double	ny;
	double	s;

	s = game->player.speed;
	nx = game->player.map_pos.x - cos(game->player.dir + M_PI_2) * s;
	ny = game->player.map_pos.y - sin(game->player.dir + M_PI_2) * s;
	if (!is_position_blocked(game, nx, game->player.map_pos.y))
		game->player.map_pos.x = nx;
	if (!is_position_blocked(game, game->player.map_pos.x, ny))
		game->player.map_pos.y = ny;
	game->player.pos_x = game->player.map_pos.x;
	game->player.pos_y = game->player.map_pos.y;
	draw_frame(game);
}

/**
 * Déplace le joueur vers la droite (strafe) avec glissement
 */
void	move_player_right(t_game *game)
{
	double	nx;
	double	ny;
	double	s;

	s = game->player.speed;
	nx = game->player.map_pos.x + cos(game->player.dir + M_PI_2) * s;
	ny = game->player.map_pos.y + sin(game->player.dir + M_PI_2) * s;
	if (!is_position_blocked(game, nx, game->player.map_pos.y))
		game->player.map_pos.x = nx;
	if (!is_position_blocked(game, game->player.map_pos.x, ny))
		game->player.map_pos.y = ny;
	game->player.pos_x = game->player.map_pos.x;
	game->player.pos_y = game->player.map_pos.y;
	draw_frame(game);
}
