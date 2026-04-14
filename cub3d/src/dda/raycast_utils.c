/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:37:29 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/21 23:13:12 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Vérifie si des coordonnées sont dans les limites de la carte
 * @param game structure principale
 * @param x position x en pixels
 * @param y position y en pixels
 * @return 1 si valide, 0 sinon
 */
int	coords_within_boundaries(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map_width * CUBE_SIZE && y >= 0
		&& y < game->map_height * CUBE_SIZE)
		return (1);
	return (0);
}

/**
 * Vérifie si les coordonnées correspondent à un mur
 * @param game structure principale
 * @param x position x en pixels
 * @param y position y en pixels
 * @return 1 si la case est un mur, 0 sinon
 */
int	is_wall(t_game *game, int x, int y)
{
	x = (int)(x / CUBE_SIZE);
	y = (int)(y / CUBE_SIZE);
	if (game->map[y][x] == '1')
		return (1);
	return (0);
}

/**
 * Remplit les infos d’un rayon vertical touché par un mur
 * @param ray structure du rayon
 * @param game structure principale
 * @param calc variables du calcul DDA
 * @param right 1 si le rayon va vers la droite, 0 sinon
 */
void	fill_ray_vertical(t_ray *ray, t_game *game, t_ray_calc calc, int right)
{
	ray->distance = sqrt(pow(calc.x - game->player.map_pos.x, 2) + pow(calc.y
				- game->player.map_pos.y, 2));
	ray->point.x = calc.x;
	ray->point.y = calc.y;
	ray->axis = 1;
	if (right)
		ray->face = EAST;
	else
		ray->face = WEST;
}

/**
 * Remplit les infos d’un rayon horizontal touché par un mur
 * @param ray structure du rayon
 * @param calc variables du calcul DDA
 * @param up 1 si le rayon va vers le haut, 0 sinon
 */
void	fill_ray_horizontal(t_ray *ray, t_ray_calc calc, int up)
{
	ray->point.x = calc.x;
	ray->point.y = calc.y;
	ray->axis = 0;
	if (up)
		ray->face = NORTH;
	else
		ray->face = SOUTH;
}

/**
 * Calcule approximativement la coordonnée y d’un mur touché
 * @param calc variables du calcul DDA
 * @param up 1 si le rayon monte, 0 sinon
 * @return coordonnée y ajustée
 */
double	get_wall_y(t_ray_calc calc, int up)
{
	if (up)
		return (floor(calc.y - 1));
	else
		return (floor(calc.y));
}
