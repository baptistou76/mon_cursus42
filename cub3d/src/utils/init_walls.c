/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:47:45 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/29 01:06:51 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Initialise un pointeur texture avec malloc et memset
 * @param tex adresse du pointeur à initialiser
 * @return 1 si succès, 0 sinon
 */
static int	init_all_textures(t_texture **tex)
{
	*tex = malloc(sizeof(t_texture));
	if (!*tex)
		return (print_error("malloc failed\n", 0));
	ft_memset(*tex, 0, sizeof(t_texture));
	return (1);
}

/**
 * Initialise la texture nord (NO)
 */
int	init_tex_north(t_game *game)
{
	return (init_all_textures(&game->tex_north));
}

/**
 * Initialise la texture sud (SO)
 */
int	init_tex_south(t_game *game)
{
	return (init_all_textures(&game->tex_south));
}

/**
 * Initialise la texture est (EA)
 */
int	init_tex_east(t_game *game)
{
	return (init_all_textures(&game->tex_east));
}

/**
 * Initialise la texture ouest (WE)
 */
int	init_tex_west(t_game *game)
{
	return (init_all_textures(&game->tex_west));
}
