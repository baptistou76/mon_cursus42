/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:01:14 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 19:42:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_command_line_arguments(int argc, char **argv, t_game *game)
{
	int	map_params_len;

	game->map_alloc = false;
	if (argc > 2)
		ft_error("Error: Too many args\n", game);
	if (argc < 2)
		ft_error("Error: Map is missingt\n", game);
	map_params_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_params_len - 4], ".ber", 4))
		ft_error("Error: Map must be a (.ber) file", game);
}

void	init_map(t_game *game, char *argv)
{
	char	*map_temp;
	char	*line_temp;
	int		map_fd;

	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		ft_error("The map couldn't be opened\n", game);
	map_temp = ft_strdup("");
	game->map.rows = 0;
	while (true)
	{
		line_temp = get_next_line(map_fd);
		if (line_temp == NULL)
			break ;
		map_temp = ft_strappend(&map_temp, line_temp);
		free(line_temp);
		game->map.rows++;
	}
	close(map_fd);
	check_for_empty_line(map_temp, game);
	game->map.entire = ft_split(map_temp, '\n');
	game->map_alloc = true;
	free(map_temp);
}

void	check_empty_start(char *map, t_game *game)
{
	if (map[0] == '\n')
	{
		free(map);
		ft_error("Invalid map: Empty line detected at begin\n", game);
	}
}

void	check_empty_end(char *map, t_game *game)
{
	int	len;

	len = ft_strlen(map);
	if (len > 0 && map[len - 1] == '\n')
	{
		free(map);
		ft_error("Invalid map: Empty line detected at the end\n", game);
	}
}

void	check_empty_middle(char *map, t_game *game)
{
	int	i;

	i = 0;
	while (map[i + 1])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			free(map);
			ft_error("Invalid map: Empty line detected in the middle\n", game);
		}
		i++;
	}
}
