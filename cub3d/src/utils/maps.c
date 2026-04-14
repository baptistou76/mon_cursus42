/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:49:33 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/21 01:45:16 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Vérifie si le caractère correspond à une orientation du joueur
 * @param c caractère à tester
 * @return 1 si c est 'N', 'S', 'E' ou 'W', 0 sinon
 */
int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/**
 * Vérifie si le caractère est valide dans une carte
 * @param c caractère à tester
 * @return 1 si valide (' ', '0', '1', ou joueur), 0 sinon
 */
int	is_map_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || is_player_char(c))
		return (1);
	return (0);
}

/**
 * Vérifie si une ligne appartient à la description de la carte
 * @param line ligne du fichier .cub
 * @return 1 si c'est une ligne de carte, 0 sinon
 */
int	is_map_line(char *line)
{
	if (!line || line[0] == '\0' || line[0] == '\n')
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (0);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (0);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (0);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (0);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (0);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (0);
	return (1);
}

/**
 * Initialise la structure de jeu (textures, couleurs, dimensions, joueur)
 * @param game structure principale
 * @return 1 si succès, 0 sinon
 */
int	init_game_data(t_game *game)
{
	if (!init_tex_north(game) || !init_tex_south(game) || !init_tex_east(game)
		|| !init_tex_west(game))
		return (0);
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->map_width = 0;
	game->map_height = 0;
	game->map = NULL;
	game->player.map_pos.x = 0;
	game->player.map_pos.y = 0;
	game->player.dir = 0;
	game->rays = NULL;
	return (1);
}

/**
 * Alloue le tableau 2D de la carte
 * @param game structure principale
 * @param height hauteur de la carte
 * @param width largeur de la carte
 * @return 1 si succès, 0 sinon
 */
int	init_map_array(t_game *game, int height, int width)
{
	int	i;

	game->map = malloc(sizeof(char *) * (height + 1));
	if (!game->map)
		return (free_textures(game), print_error("malloc failed\n", 0));
	game->map[height] = NULL;
	i = 0;
	while (i < height)
	{
		game->map[i] = malloc(sizeof(char) * (width + 1));
		if (!game->map[i])
			return (free_allocated_array(&game->map, i),
				print_error("malloc failed\n", 0));
		game->map[i][width] = '\0';
		while ((i == height - 1) && width > 0)
			game->map[i][--width] = ' ';
		i++;
	}
	return (1);
}
