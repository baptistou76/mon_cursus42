/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:48:28 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/19 22:56:33 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Vérifie s'il y a un mur ou un vide en bas du joueur
 * @param game structure principale
 * @param new_x nouvelle coordonnée x (pixels)
 * @param new_y nouvelle coordonnée y (pixels)
 * @return 1 si bloqué, 0 sinon
 */
int	is_blocking_down(t_game *game, int new_x, int new_y)
{
	new_x += 16;
	new_y += 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= game->map_width || new_y < 0
		|| new_y >= game->map_height)
		return (1);
	if (game->map[new_y][new_x] == '1' || game->map[new_y + 1][new_x
		+ 1] == ' ')
		return (1);
	return (0);
}

/**
 * Vérifie s'il y a un mur ou un vide au-dessus du joueur
 */
int	is_blocking_up(t_game *game, int new_x, int new_y)
{
	new_x -= 16;
	new_y -= 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= game->map_width || new_y < 0
		|| new_y >= game->map_height)
		return (1);
	if (game->map[new_y][new_x] == '1' || game->map[new_y + 1][new_x
		+ 1] == ' ')
		return (1);
	return (0);
}

/**
 * Vérifie s'il y a un mur ou un vide à droite du joueur
 */
int	is_blocking_right(t_game *game, int new_x, int new_y)
{
	new_x += 16;
	new_y -= 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= game->map_width || new_y < 0
		|| new_y >= game->map_height)
		return (1);
	if (game->map[new_y][new_x] == '1' || game->map[new_y + 1][new_x
		+ 1] == ' ')
		return (1);
	return (0);
}

/**
 * Vérifie s'il y a un mur ou un vide à gauche du joueur
 */
int	is_blocking_left(t_game *game, int new_x, int new_y)
{
	new_x -= 16;
	new_y += 16;
	new_x /= CUBE_SIZE;
	new_y /= CUBE_SIZE;
	if (new_x < 0 || new_x >= game->map_width || new_y < 0
		|| new_y >= game->map_height)
		return (1);
	if (game->map[new_y][new_x] == '1' || game->map[new_y + 1][new_x
		+ 1] == ' ')
		return (1);
	return (0);
}
