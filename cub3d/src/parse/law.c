/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   law.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:35:01 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/29 00:11:07 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Vérifie si toutes les textures et couleurs ont bien été chargées
 * @param game structure principale
 * @return 1 si tout est présent, 0 sinon
 */
int	textures_colors_complete(t_game *game)
{
	if (!game->tex_north || !game->tex_south || !game->tex_east
		|| !game->tex_west)
		return (0);
	if (game->floor_color < 0 || game->ceiling_color < 0)
		return (0);
	if (!game->tex_north->img || !game->tex_south->img || !game->tex_east->img
		|| !game->tex_west->img)
		return (0);
	return (1);
}

/**
 * Vérifie que la carte contient exactement un joueur
 * @param map tableau 2D représentant la carte
 * @return 1 si un seul joueur, 0 sinon (erreur)
 */
int	map_have_one_player(char **map)
{
	int	i;
	int	j;
	int	player_found;

	player_found = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!player_found && is_player_char(map[i][j]))
				player_found = 1;
			else if (player_found && is_player_char(map[i][j]))
				return (print_error("too many players\n", 0));
			j++;
		}
		i++;
	}
	if (!player_found)
		return (print_error("no player specified in map description\n", 0));
	return (1);
}

/**
 * Vérifie que les cases autour d’un point sont valides (pas ouvertes)
 * @param map carte
 * @param i ligne
 * @param j colonne
 * @return 1 si les cases autour sont valides, 0 sinon
 */
int	valid_surroundings(char **map, int i, int j)
{
	if ((i == 0 || j == 0) && map[i][j] == '0')
		return (0);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' '
		|| map[i][j + 1] == ' ' || !map[i - 1][j] || !map[i + 1][j] || !map[i][j
		- 1] || !map[i][j + 1])
		return (0);
	return (1);
}

/**

	* Vérifie que la carte est bien fermée par des murs
		(aucun espace autour d’un 0 ou d’un joueur)
 * @param map tableau 2D représentant la carte
 * @return 1 si la carte est bien fermée, 0 sinon
 */
int	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]) && !valid_surroundings(map, i, j))
				return (print_error("map is not closed\n", 0));
			if (map[i][j] == '0' && !valid_surroundings(map, i, j))
				return (print_error("map is not closed\n", 0));
			j++;
		}
		i++;
	}
	return (1);
}
