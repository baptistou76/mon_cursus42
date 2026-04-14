/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:41:40 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/31 03:06:37 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Dessine l’image complète colonne par colonne
 * Chaque rayon génère deux colonnes de pixels (2x NB_RAYS)
 * @param game structure principale du jeu
 */
static void	draw_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_RAYS)
	{
		if (game->rays[i].distance > 0)
		{
			draw_slice(game, game->rays[i], 2 * i);
			draw_slice(game, game->rays[i], 2 * i + 1);
		}
		i++;
	}
}

/**
 * Lance NB_RAYS rayons depuis la position du joueur
 * Utilise la fonction de DDA pour détecter les murs
 * Les résultats sont stockés dans game->rays
 * @param game structure principale
 */
static void	raycasting(t_game *game)
{
	int		i;
	double	ray_angle;

	if (game->rays)
		free(game->rays);
	game->rays = malloc(sizeof(t_ray) * NB_RAYS);
	if (!game->rays)
	{
		print_error("malloc failed\n", 0);
		free_game(game);
	}
	ray_angle = game->player.dir - (HALF_FOV * DEG_RAD);
	ray_angle = normalize_angle(ray_angle);
	i = -1;
	while (++i < NB_RAYS)
	{
		cast_ray(game, ray_angle, &game->rays[i]);
		ray_angle += ANGLE_INCR;
		ray_angle = normalize_angle(ray_angle);
	}
}

/**
 * Initialise une nouvelle image (screen buffer)
 * Détruit l’ancienne si elle existe
 * @param game structure principale du jeu
 */
static void	init_image(t_game *game)
{
	if (game->screen.img)
	{
		mlx_destroy_image(game->mlx, game->screen.img);
		game->screen.img = NULL;
	}
	game->screen.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen.img)
		free_game(game);
	game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp,
			&game->screen.line_len, &game->screen.endian);
	if (!game->screen.addr)
		free_game(game);
}

/**
 * Génère et affiche une frame complète du jeu
 * Inclut le raycasting, la minimap et le rendu de l’image
 * @param game structure principale
 */
void	draw_frame(t_game *game)
{
	init_image(game);
	raycasting(game);
	draw_image(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
