/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:32:13 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/29 01:07:41 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Analyse une ligne du fichier .cub
 * - Si c’est une texture : la charge
 * - Si c’est une couleur : la stocke
 * - Sinon, si c’est une ligne de map : prépare largeur/hauteur
 * @param line ligne à analyser
 * @param game structure principale
 * @return 1 si succès, 0 si erreur
 */
int	parse_line(char *line, t_game *game)
{
	static int	max_width = 0;
	static int	height = 0;
	int			add_t;
	int			add_c;

	if (!line || line[0] == '\0' || line[0] == '\n')
		return (1);
	add_t = add_texture(game, line);
	if (add_t == 1 || add_t == 0)
		return (add_t);
	add_c = add_color(game, line);
	if (add_c == 1 || add_c == 0)
		return (add_c);
	if (textures_colors_complete(game) && is_map_char(line[0]))
	{
		height++;
		if ((int)strlen_without_nl(line) > max_width)
			max_width = strlen_without_nl(line);
	}
	else
		return (print_error("invalid character found in file\n", 0));
	game->map_height = height + 1;
	game->map_width = max_width;
	return (1);
}

/**
 * Remplit une ligne de la carte dans le tableau
 * Remplace les caractères invalides ou manquants par des espaces
 * @param line ligne du fichier
 * @param game structure du jeu
 * @param row index de la ligne dans le tableau
 * @return 1 si succès, 0 si erreur
 */
static int	fill_map_row(char *line, t_game *game, int row)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			game->map[row][i] = line[i];
		else
			return (print_error("invalid character in map description\n", 0));
		i++;
	}
	while (i < game->map_width)
	{
		game->map[row][i] = ' ';
		i++;
	}
	game->map[row][i] = '\0';
	return (1);
}

/**
 * Remplit le tableau de la carte en lisant le fichier
 * @param path chemin du fichier .cub
 * @param game structure du jeu
 * @return 1 si succès, 0 sinon
 */
static int	fill_map_array(char *path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("unable to open map\n", 0));
	line = "";
	i = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (is_map_line(line))
		{
			if (!fill_map_row(line, game, i++))
			{
				free(line);
				return (close(fd));
			}
		}
		free(line);
	}
	close(fd);
	return (1);
}

/**
 * Parse entièrement un fichier .cub et remplit la structure de jeu
 * - Récupère textures, couleurs, carte, position du joueur
 * - Vérifie la validité de la map
 * @param path chemin vers le fichier .cub
 * @param game structure principale
 * @return 1 si succès, 0 sinon
 */
int	parse_map(char *path, t_game *game)
{
	if (!scan_map(path, game))
		return (0);
	if (!init_map_array(game, game->map_height, game->map_width))
		return (free_textures(game));
	if (fill_map_array(path, game) <= 0)
	{
		free_allocated_array(&game->map, 0);
		return (free_textures(game));
	}
	if (!map_have_one_player(game->map))
	{
		free_allocated_array(&game->map, 0);
		return (free_textures(game));
	}
	if (!is_map_closed(game->map))
	{
		free_allocated_array(&game->map, 0);
		return (free_textures(game));
	}
	get_player_start(game);
	return (1);
}
