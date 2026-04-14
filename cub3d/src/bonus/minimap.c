/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:31:44 by bcaumont          #+#    #+#             */
/*   Updated: 2025/07/31 02:59:23 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Dessine un carré plein à une position donnée sur l’image
 */
static void	draw_square(t_image *img, t_point pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}

/**
 * Détermine la couleur d'une case de la minimap
 */
static int	get_minimap_tile_color(char tile)
{
	if (tile == ' ')
		return (-1);
	if (tile == '1')
		return (0xAAAAAA);
	if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (0x000000);
	return (0x000000);
}

/**
 * Dessine toutes les cases valides de la minimap
 */
static void	draw_minimap_tiles(t_game *game, int scale)
{
	t_point	pos;
	int		color;
	int		x;
	int		y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			color = get_minimap_tile_color(game->map[y][x]);
			if (color != -1)
			{
				pos.x = MINIMAP_MARGIN + x * scale;
				pos.y = MINIMAP_MARGIN + y * scale;
				draw_square(&game->screen, pos, scale, color);
			}
			x++;
		}
		y++;
	}
}

/**
 * Dessine la position et la direction du joueur sur la minimap
 */
static void	draw_player(t_game *game, int scale)
{
	t_point	center;
	t_point	dir;

	center.x = MINIMAP_MARGIN + (game->player.pos_x / CUBE_SIZE) * scale;
	center.y = MINIMAP_MARGIN + (game->player.pos_y / CUBE_SIZE) * scale;
	draw_square(&game->screen, (t_point){center.x - 2, center.y - 2}, 4,
		0xFF0000);
	dir.x = center.x + cos(game->player.dir) * 10;
	dir.y = center.y + sin(game->player.dir) * 10;
	ft_draw_line(&game->screen, center, dir, 0xFF0000);
}

/**
 * Fonction principale pour dessiner la minimap
 */
void	draw_minimap(t_game *game)
{
	draw_minimap_tiles(game, MINIMAP_SCALE);
	draw_player(game, MINIMAP_SCALE);
}
