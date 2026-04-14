/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:02:30 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 17:48:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_path_to_exit(t_game *game)
{
	int		check;
	char	**copy;

	copy = copy_map(game->map.entire);
	if (!copy)
		ft_error("Error: Memory allocation failed\n", game);
	ft_flood_fill(copy, game->map.player.x, game->map.player.y);
	check = ft_is_map_valid(copy);
	free_map(copy);
	if (check == 0)
		ft_error("Error: Map can't be finished\n", game);
	return (check);
}

char	**copy_map(char **map)
{
	int		y;
	char	**copy;

	y = 0;
	while (map[y])
		y++;
	copy = malloc(sizeof(char *) * (y + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (map[y])
	{
		copy[y] = ft_strdup(map[y]);
		if (!copy[y])
		{
			free_map(copy);
			return (NULL);
		}
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

void	ft_flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'Z'
		|| map[y][x] == 'z')
		return ;
	map[y][x] = 'F';
	ft_flood_fill(map, x + 1, y);
	ft_flood_fill(map, x - 1, y);
	ft_flood_fill(map, x, y + 1);
	ft_flood_fill(map, x, y - 1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	ft_is_map_valid(char **copy)
{
	int	i;
	int	j;

	i = 0;
	while (copy[i] != NULL)
	{
		j = 0;
		while (copy[i][j] != '\0')
		{
			if (copy[i][j] == 'C')
				return (0);
			if (copy[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
