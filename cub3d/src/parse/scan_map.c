/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:00:44 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/29 01:20:10 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	scan_map_loop(int fd, t_game *game)
{
	char	*line;
	int		err;

	line = "";
	err = 0;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!err && !parse_line(line, game))
			err = 1;
		if (textures_colors_complete(game) && game->map_height > 0
			&& (line[0] == '\n' || line[0] == '\0'))
			err = print_error("map has an empty line\n", 1);
		free(line);
	}
	return (err);
}

int	scan_map(char *path, t_game *game)
{
	int	fd;
	int	err;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("unable to open map\n", 0));
	if (!init_game_data(game))
		return (0);
	err = scan_map_loop(fd, game);
	close(fd);
	if (err)
		return (free_textures(game));
	return (1);
}
