/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:56:57 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/22 00:09:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * Initialise la fenêtre de jeu avec la mlx
 * @param game structure principale contenant mlx et win
 * @return EXIT_SUCCESS ou message d'erreur avec EXIT_FAILURE
 */
static int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("mlx_init() failed\n", EXIT_FAILURE));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (print_error("mlx_new_window() failed\n", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

/**
 * Point d’entrée principal du programme cub3D
 * Vérifie les arguments, initialise la fenêtre, parse la carte,
 * puis lance la boucle principale du jeu.
 */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, (sizeof(t_game)));
	if (argc != 2)
		return (print_error("Error: Wrong number of arguments\n",
				EXIT_FAILURE));
	if (!is_file_extension_correct(argv[1]))
		return (print_error("Wrong file extension\n", EXIT_FAILURE));
	if (init_game(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (!parse_map(argv[1], &game))
	{
		mlx_destroy_window(game.mlx, game.win);
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		return (EXIT_FAILURE);
	}
	game.has_focus = 1;
	game_loop(&game);
	return (0);
}
