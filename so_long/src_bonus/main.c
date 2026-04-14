/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:41:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 14:24:27 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Error: Map missing\n");
		exit(1);
	}
	game = malloc(sizeof(t_game));
	check_command_line_arguments(argc, argv, game);
	init_map(game, argv[1]);
	init_variables(game);
	map_checker(game);
	init_mlx(game);
	init_sprites(game);
	render_map(game);
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, handle_inputs, game);
	mlx_hook(game->mlx_win, 17, 0, close_game, game);
	mlx_hook(game->mlx_win, Expose, ExposureMask, render_map, game);
	mlx_loop(game->mlx_ptr);
	free_allocated_memory(game);
}
