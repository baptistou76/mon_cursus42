/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:50:41 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/04 19:44:01 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX/mlx.h"
# include "../MLX/mlx_int.h"
# include "../lib/libft.h"

# define PLAYER 'P'
# define COIN 'C'
# define WALL '1'
# define FLOOR '0'
# define EXIT 'E'

# define WALL_XPM "xpm/wall.xpm"
# define EXIT_XPM "xpm/exit.xpm"
# define COIN_XPM "xpm/virus.xpm"
# define FLOOR_XPM "xpm/floor.xpm"
# define PLAYER_R_XPM "xpm/hunk_w.xpm"
# define PLAYER_L_XPM "xpm/hunk_l.xpm"

# define FRONT 1
# define LEFT 2
# define RIGHT 3
# define BACK 4

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113

# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_ESC 65307

typedef struct s_pos
{
	int		x;
	int		y;

}			t_pos;

typedef struct s_imgs
{
	void	*xpm_ptr;
	int		x;
	int		y;
}			t_imgs;

typedef struct s_map
{
	char	**entire;
	int		rows;
	int		columns;
	int		coins;
	int		exit;
	int		players;
	t_pos	player;
}			t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		movements;
	int		player_sprite;
	bool	map_alloc;
	t_map	map;
	t_imgs	wall;
	t_imgs	floor;
	t_imgs	coins;
	t_imgs	open_exit;
	t_imgs	closed_exit;
	t_imgs	player_right;
	t_imgs	player_left;

}			t_game;

void		ft_free_map(t_game *game);
void		ft_destroy_images(t_game *game);
void		free_allocated_memory(t_game *game);
void		init_variables(t_game *game);
void		init_mlx(t_game *game);
void		init_sprites(t_game *game);
t_imgs		new_sprite(void *mlx, char *path, t_game *game);
void		check_for_empty_line(char *map, t_game *game);
void		init_map(t_game *game, char *argv);
void		check_command_line_arguments(int argc, char **argv, t_game *game);
int			handle_inputs(int keysym, t_game *game);
void		player_move(t_game *game, int new_y, int new_x, int player_sprite);
void		map_checker(t_game *game);
void		rows_checker(t_game *game);
void		columns_checker(t_game *game);
void		params_counter(t_game *game);
void		params_map_checker(t_game *game);
void		print_movements(t_game *game);
void		render_sprite(t_game *game, t_imgs sprite, int line, int columns);
void		render_player(t_game *game, int y, int x);
void		identify_sprite(t_game *game, int y, int x);
int			render_map(t_game *game);
int			ft_error(char *msg, t_game *game);
int			close_game(t_game *game);
int			victory(t_game *game);
int			check_path_to_exit(t_game *game);
char		**copy_map(char **map);
void		ft_flood_fill(char **map, int x, int y);
void		free_map(char **map);
void		update_position(t_game *game, int new_y, int new_x,
				char *under_player);
void		handle_coin(t_game *game, char *under_player);
int			can_move_to(t_game *game, int y, int x);
int			ft_is_map_valid(char **copy);
void		check_empty_middle(char *map, t_game *game);
void		check_empty_end(char *map, t_game *game);
void		check_empty_start(char *map, t_game *game);

#endif