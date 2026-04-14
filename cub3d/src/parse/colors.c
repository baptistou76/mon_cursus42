/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:31:19 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/19 21:13:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Vérifie si la chaîne de caractères contient une couleur valide
 * La chaîne peut contenir des espaces, mais uniquement des chiffres sinon
 * @param str chaîne à analyser
 * @return valeur entière de la couleur ou -1 si invalide
 */
static int	parse_color_component(char *str)
{
	char	*tmp;
	int		i;
	int		col;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (strlen_without_nl(&str[i]) == 0)
		return (-1);
	tmp = strdup_trimmed(&str[i]);
	i = 0;
	while (tmp[i] && ft_isdigit(tmp[i]))
		i++;
	while (tmp[i])
	{
		if (tmp[i] != ' ')
		{
			free(tmp);
			return (-1);
		}
		i++;
	}
	col = ft_atoi(tmp);
	free(tmp);
	return (col);
}

/**
 * Convertit une chaîne "R,G,B" en une couleur MLX
 * @param str chaîne représentant une couleur (ex: "220,100,0")
 * @return couleur MLX ou -1 si erreur
 */
static int	parse_rgb_color(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**parts;

	parts = ft_split(str, ',');
	if (!parts)
		return (print_error("malloc failed\n", -1));
	if (ft_char_array_len(parts) != 3)
	{
		free_allocated_array(&parts, 0);
		return (print_error("invalid color format\n", -1));
	}
	r = parse_color_component(parts[0]);
	g = parse_color_component(parts[1]);
	b = parse_color_component(parts[2]);
	free_allocated_array(&parts, 0);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("invalid color\n", -1));
	return (create_color(0, r, g, b));
}

/**
 * Ajoute la couleur du sol (F) à la structure du jeu
 * @param line ligne contenant la couleur
 * @param game structure principale
 * @return 1 en cas de succès, 0 sinon
 */
static int	add_floor_color(char *line, t_game *game)
{
	int	i;
	int	col;

	if (game->floor_color != -1)
		return (print_error("double definition of a color (F)\n", 0));
	i = 1;
	while (line[i] == ' ')
		i++;
	col = parse_rgb_color(&line[i]);
	if (col < 0)
		return (0);
	game->floor_color = col;
	return (1);
}

/**
 * Ajoute la couleur du plafond (C) à la structure du jeu
 * @param line ligne contenant la couleur
 * @param game structure principale
 * @return 1 en cas de succès, 0 sinon
 */
static int	add_ceiling_color(char *line, t_game *game)
{
	int	i;
	int	col;

	if (game->ceiling_color != -1)
		return (print_error("double definition of a color (C)\n", 0));
	i = 1;
	while (line[i] == ' ')
		i++;
	col = parse_rgb_color(&line[i]);
	if (col < 0)
		return (0);
	game->ceiling_color = col;
	return (1);
}

/**
 * Analyse une ligne pour ajouter une couleur (sol ou plafond)
 * @param game structure principale
 * @param line ligne issue du fichier .cub
 * @return 1 si succès, 0 sinon, -1 si ligne non reconnue
 */
int	add_color(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (add_floor_color(line, game));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (add_ceiling_color(line, game));
	return (-1);
}
