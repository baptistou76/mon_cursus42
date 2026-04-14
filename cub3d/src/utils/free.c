/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:46:00 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/19 21:37:08 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Libère toutes les ressources allouées dans la structure principale
 * Détruit les textures, images, fenêtre, display et quitte le programme
 * @param game structure principale du jeu
 * @return toujours 0 (inutile car exit)
 */
int	free_game(t_game *game)
{
	int	i;

	free(game->rays);
	i = 0;
	while (i < game->map_height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	mlx_destroy_image(game->mlx, game->tex_north->img);
	mlx_destroy_image(game->mlx, game->tex_south->img);
	mlx_destroy_image(game->mlx, game->tex_east->img);
	mlx_destroy_image(game->mlx, game->tex_west->img);
	free(game->tex_north);
	free(game->tex_south);
	free(game->tex_east);
	free(game->tex_west);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * Libère un tableau de chaînes alloué dynamiquement
 * @param array pointeur vers le tableau
 * @param is_err 1 pour afficher une erreur, 0 sinon
 * @return -1 si erreur, 0 sinon
 */
int	free_allocated_array(char ***array, int is_err)
{
	int	i;

	if (!*array)
		return (0);
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	if (is_err)
		return (print_error("invalid caracter detected\n", -1));
	return (0);
}

/**
 * Détruit les textures chargées et libère leur structure
 * @param game structure principale
 * @return toujours 0
 */
int	free_textures(t_game *game)
{
	if (game->tex_north->is_init)
		mlx_destroy_image(game->mlx, game->tex_north->img);
	if (game->tex_south->is_init)
		mlx_destroy_image(game->mlx, game->tex_south->img);
	if (game->tex_east->is_init)
		mlx_destroy_image(game->mlx, game->tex_east->img);
	if (game->tex_west->is_init)
		mlx_destroy_image(game->mlx, game->tex_west->img);
	free(game->tex_north);
	free(game->tex_south);
	free(game->tex_east);
	free(game->tex_west);
	return (0);
}

/**
 * Libère partiellement un tableau jusqu’à un certain index
 * @param array tableau à libérer
 * @param last_alloc dernier index alloué
 */
void	free_partial(char ***array, int last_alloc)
{
	int	i;

	i = 0;
	while (i < last_alloc)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
}
