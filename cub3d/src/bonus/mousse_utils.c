/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousse_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 03:04:48 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/31 03:13:55 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Calcule le facteur de rotation en fonction des touches pressées
 */
static double	get_rotation_factor(t_game *game)
{
	if (game->keys.forward || game->keys.backward || game->keys.left
		|| game->keys.right)
		return (0.3);
	return (0.5);
}

/**
 * Gère la rotation de la vue en fonction de la souris
 * Ajuste la vitesse selon si le joueur bouge ou non
 * @param game structure principale
 */
static void	handle_mouse(t_game *game)
{
	int		mouse_x;
	int		mouse_y;
	int		center_x;
	double	angle;
	double	rotation_factor;

	center_x = WIDTH / 2;
	rotation_factor = get_rotation_factor(game);
	mlx_mouse_get_pos(game->mlx, game->win, &mouse_x, &mouse_y);
	if (mouse_x != center_x)
	{
		angle = (mouse_x - center_x) * 0.003 * rotation_factor;
		game->player.dir += angle;
		game->player.dir = normalize_angle(game->player.dir);
		mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	}
}

/**
 * Fonction appelée à chaque boucle de jeu
 * Met à jour la position du joueur, l’angle, et affiche une frame
 * @param game structure principale
 * @return 0 toujours (utilisé par mlx_loop_hook)
 */
int	update_game(t_game *game)
{
	if (!game->has_focus)
		return (0);
	update_player(game);
	handle_mouse(game);
	draw_frame(game);
	return (0);
}
