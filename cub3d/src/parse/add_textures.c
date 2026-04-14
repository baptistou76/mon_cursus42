/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:36:08 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/21 02:46:58 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Charge la texture nord et la stocke dans la structure du jeu
 * @param line ligne contenant le chemin vers la texture
 * @param game structure principale
 * @return 1 si succès, 0 sinon
 */
static int	add_north_texture(char *line, t_game *game)
{
	int		i;
	char	*path;

	if (game->tex_north->is_init)
		return (print_error("double definition of a texture (NO)\n", 0));
	i = 2;
	while (line[i] == ' ')
		i++;
	path = strdup_trimmed(&line[i]);
	if (!path)
		return (print_error("malloc failed\n", 0));
	if (!load_texture(game, game->tex_north, path))
	{
		free(path);
		return (0);
	}
	game->tex_north->is_init = 1;
	free(path);
	return (1);
}

/**
 * Charge la texture sud
 */
static int	add_south_texture(char *line, t_game *game)
{
	int		i;
	char	*path;

	if (game->tex_south->is_init)
		return (print_error("double definition of a texture (SO)\n", 0));
	i = 2;
	while (line[i] == ' ')
		i++;
	path = strdup_trimmed(&line[i]);
	if (!path)
		return (print_error("malloc failed\n", 0));
	if (!load_texture(game, game->tex_south, path))
	{
		free(path);
		return (0);
	}
	game->tex_south->is_init = 1;
	free(path);
	return (1);
}

/**
 * Charge la texture est
 */
static int	add_east_texture(char *line, t_game *game)
{
	int		i;
	char	*path;

	if (game->tex_east->is_init)
		return (print_error("double definition of a texture (EA)\n", 0));
	i = 2;
	while (line[i] == ' ')
		i++;
	path = strdup_trimmed(&line[i]);
	if (!path)
		return (print_error("malloc failed\n", 0));
	if (!load_texture(game, game->tex_east, path))
	{
		free(path);
		return (0);
	}
	game->tex_east->is_init = 1;
	free(path);
	return (1);
}

/**
 * Charge la texture ouest
 */
static int	add_west_texture(char *line, t_game *game)
{
	int		i;
	char	*path;

	if (game->tex_west->is_init)
		return (print_error("double definition of a texture (WE)\n", 0));
	i = 2;
	while (line[i] == ' ')
		i++;
	path = strdup_trimmed(&line[i]);
	if (!path)
		return (print_error("malloc failed\n", 0));
	if (!load_texture(game, game->tex_west, path))
	{
		free(path);
		return (0);
	}
	game->tex_west->is_init = 1;
	free(path);
	return (1);
}

/**

	* Analyse une ligne de type texture (NO/SO/WE/EA)
	et appelle la fonction adaptée
 * @param game structure principale
 * @param line ligne du fichier .cub
 * @return 1 si texture ajoutée, 0 si erreur, -1 si ligne non reconnue
 */
int	add_texture(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (add_north_texture(line, game));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (add_south_texture(line, game));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (add_west_texture(line, game));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (add_east_texture(line, game));
	return (-1);
}
