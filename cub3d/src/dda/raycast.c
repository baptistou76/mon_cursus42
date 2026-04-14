/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:39:00 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/21 01:45:07 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Initialise les variables pour un rayon vertical (DDA)
 * @param r vars du rayon
 * @param game structure principale
 * @param right 1 si le rayon va à droite
 * @return structure mise à jour
 */
static t_ray_calc	get_vertical_calc(t_ray_calc r, t_game *game, int right)
{
	double	slope;

	slope = r.angle_sin / r.angle_cos;
	if (right)
		r.delta_x = 1;
	else
		r.delta_x = -1;
	r.delta_y = r.delta_x * slope;
	if (right)
		r.x = ceil(game->player.map_pos.x);
	else
		r.x = floor(game->player.map_pos.x);
	r.y = game->player.map_pos.y + (r.x - game->player.map_pos.x) * slope;
	return (r);
}

/**
 * Initialise les variables pour un rayon horizontal (DDA)
 * @param r vars du rayon
 * @param game structure principale
 * @param up 1 si le rayon va vers le haut
 * @return structure mise à jour
 */
static t_ray_calc	get_horizontal_calc(t_ray_calc r, t_game *game, int up)
{
	double	slope;

	slope = r.angle_cos / r.angle_sin;
	if (up)
		r.delta_y = -1;
	else
		r.delta_y = 1;
	r.delta_x = r.delta_y * slope;
	if (up)
		r.y = floor(game->player.map_pos.y);
	else
		r.y = ceil(game->player.map_pos.y);
	r.x = game->player.map_pos.x + (r.y - game->player.map_pos.y) * slope;
	return (r);
}

/**
 * Recherche du mur vertical touché par le rayon
 * @param r infos de calcul
 * @param game structure du jeu
 * @param ray structure du rayon à remplir
 * @param angle angle du rayon
 */
void	perform_vertical_dda(t_ray_calc r, t_game *game, t_ray *ray,
		double angle)
{
	int		right;
	double	wall_x;
	double	wall_y;

	right = 0;
	if (angle > PI_3_2 || angle < M_PI_2)
		right = 1;
	r = get_vertical_calc(r, game, right);
	while (coords_within_boundaries(game, r.x, r.y))
	{
		if (right)
			wall_x = floor(r.x);
		else
			wall_x = floor(r.x - 1);
		wall_y = floor(r.y);
		if (is_wall(game, wall_x, wall_y))
		{
			fill_ray_vertical(ray, game, r, right);
			break ;
		}
		r.x += r.delta_x;
		r.y += r.delta_y;
	}
}

/**
 * Recherche du mur horizontal touché par le rayon
 * @param r infos de calcul
 * @param game structure du jeu
 * @param ray structure du rayon à remplir
 * @param angle angle du rayon
 */
static void	perform_horizontal_dda(t_ray_calc r, t_game *game, t_ray *ray,
		double angle)
{
	int		up;
	double	wall_x;
	double	wall_y;
	double	dist;

	up = (angle < 0 || angle > M_PI);
	r = get_horizontal_calc(r, game, up);
	while (coords_within_boundaries(game, r.x, r.y))
	{
		wall_y = get_wall_y(r, up);
		wall_x = floor(r.x);
		if (is_wall(game, wall_x, wall_y))
		{
			dist = sqrt(pow(r.x - game->player.map_pos.x, 2) + pow(r.y
						- game->player.map_pos.y, 2));
			if (!ray->distance || dist < ray->distance)
			{
				ray->distance = dist;
				fill_ray_horizontal(ray, r, up);
			}
			break ;
		}
		r.x += r.delta_x;
		r.y += r.delta_y;
	}
}

/**
 * Lance un rayon à partir de l’angle donné avec DDA
 * Stocke la distance et le point de collision dans ray
 * @param game structure du jeu
 * @param ray_angle angle du rayon
 * @param ray structure du rayon à remplir
 */
void	cast_ray(t_game *game, double ray_angle, t_ray *ray)
{
	t_ray_calc	r;
	double		correction;

	ray->distance = 0;
	ray->angle = ray_angle;
	correction = cos(normalize_angle(ray_angle - game->player.dir));
	r.angle_cos = cos(ray_angle);
	r.angle_sin = sin(ray_angle);
	perform_vertical_dda(r, game, ray, ray_angle);
	perform_horizontal_dda(r, game, ray, ray_angle);
	ray->distance *= correction;
	ray->height = CUBE_SIZE / ray->distance * PROJECTION_DISTANCE;
}
