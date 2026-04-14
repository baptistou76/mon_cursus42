/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:43:46 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/19 20:54:03 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Retourne la texture correspondant à la face du mur touchée
 * @param game structure principale
 * @param side direction de la face (NORTH, SOUTH, etc.)
 * @return pointeur vers la texture correspondante
 */
static t_texture	*get_texture(t_game *game, enum e_direction side)
{
	if (side == NORTH)
		return (game->tex_north);
	else if (side == SOUTH)
		return (game->tex_south);
	else if (side == EAST)
		return (game->tex_east);
	else
		return (game->tex_west);
}

/**
 * Dessine une colonne de texture à l’écran
 * @param game structure du jeu
 * @param ray données du rayon
 * @param x position x de la colonne
 * @param offset décalage vertical pour centrer le mur
 */
static void	draw_texture_column(t_game *game, t_ray ray, int x, int offset)
{
	t_texture	*tex;
	float		scale;
	int			tex_x;
	float		tex_y;
	int			y;

	tex = get_texture(game, ray.face);
	scale = tex->height / ray.height;
	if (ray.axis == 1)
		tex_x = ray.point.y % CUBE_SIZE;
	else
		tex_x = ray.point.x % CUBE_SIZE;
	if (ray.height > HEIGHT)
		tex_y = ((ray.height - HEIGHT) / 2) * scale;
	else
		tex_y = 0;
	y = 0;
	while (y < ray.height)
	{
		put_pixel(&game->screen, x, y + offset, get_tex_color(tex, tex_x,
				(int)tex_y % tex->height));
		tex_y += scale;
		y++;
	}
}

/**
 * Dessine une tranche verticale de l’écran : plafond, mur, sol
 * @param game structure principale
 * @param ray données du rayon correspondant à cette colonne
 * @param index position x à l’écran
 */
void	draw_slice(t_game *game, t_ray ray, int index)
{
	int	i;
	int	offset;

	offset = (HEIGHT - ray.height) / 2;
	if (offset < 0)
		offset = 0;
	i = 0;
	while (i < offset)
	{
		put_pixel(&game->screen, index, i, game->ceiling_color);
		i++;
	}
	draw_texture_column(game, ray, index, i);
	i = ray.height + offset;
	while (i < HEIGHT)
	{
		put_pixel(&game->screen, index, i, game->floor_color);
		i++;
	}
}
