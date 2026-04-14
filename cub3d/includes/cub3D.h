/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:27:03 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/31 02:49:42 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../lib/lib.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
/* --- Constantes mathématiques --- */
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923
# endif

# ifndef M_PI_4
#  define M_PI_4 0.78539816339744830962
# endif

# ifndef M_2_PI
#  define M_2_PI 6.28318530717958647692
# endif

# define FOCUS_IN 9
# define FOCUS_OUT 10

/* --- Dimensions du jeu --- */
# define WIDTH 1280
# define HEIGHT 720
# define CUBE_SIZE 64
# define MINI_SIZE 8
# define PLAYER_HEIGHT 32
# define PROJECTION_DISTANCE 1108

/* --- Champs de vision --- */
# define FOV 60
# define HALF_FOV 30
# define DEG_RAD 0.017453
# define RAD_DEG 57.295780
# define TWO_PI 6.283185
# define PI_3_2 4.712389
# define ANGLE_INCR 0.001636

/* --- Paramètres du joueur --- */
# define SPEED 10.0
# define ROT_SPEED 0.06

/* --- Contrôles clavier --- */
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define FORWARD 119
# define BACKWARD 115
# define LEFT 97
# define RIGHT 100
# define ESC 65307

/* --- Nombre de rayons --- */
# define NB_RAYS 640

/* --- Positionnement de la minimap --- */
# define MINIMAP_SCALE 8
# define MINIMAP_MARGIN 10

/* --- Direction des murs --- */
enum					e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

/* --- touches --- */
typedef struct s_keys
{
	int					forward;
	int					backward;
	int					left;
	int					right;
	int					rot_left;
	int					rot_right;
}						t_keys;

/* --- Point simple en 2D --- */
typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

/* --- Données d'une image MLX --- */
typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_image;

/* --- Texture de mur --- */
typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
	int					is_init;
}						t_texture;

/* --- Informations sur un rayon projeté --- */
typedef struct s_ray
{
	t_point				point;
	float				distance;
	double				angle;
	float				wall_height;
	int					axis;
	double				height;
	enum e_direction	face;
}						t_ray;

/* --- Variables pour le calcul DDA --- */
typedef struct s_ray_calc
{
	double				angle_sin;
	double				angle_cos;
	double				delta_x;
	double				delta_y;
	double				x;
	double				y;
}						t_ray_calc;

/* --- Joueur --- */
typedef struct s_player
{
	t_point				map_pos;
	double				pos_x;
	double				pos_y;
	double				dir;
	double				speed;
}						t_player;

/* --- Structure principale du jeu --- */
typedef struct s_game
{
	void				*mlx;
	void				*win;
	int					floor_color;
	int					ceiling_color;
	int					map_width;
	int					map_height;
	int					is_focused;
	int					has_focus;
	char				**map;
	t_ray				*rays;
	t_keys				keys;
	t_player			player;
	t_image				screen;
	t_texture			*tex_north;
	t_texture			*tex_south;
	t_texture			*tex_west;
	t_texture			*tex_east;

}						t_game;

void					ft_draw_line(t_image *img, t_point p1, t_point p2,
							int col);
double					normalize_angle(double angle);
void					draw_slice(t_game *game, t_ray ray, int index);
void					draw_frame(t_game *game);
int						coords_within_boundaries(t_game *game, int x, int y);
int						is_wall(t_game *game, int x, int y);
void					fill_ray_vertical(t_ray *ray, t_game *game,
							t_ray_calc calc, int right);
void					fill_ray_horizontal(t_ray *ray, t_ray_calc calc,
							int up);
double					get_wall_y(t_ray_calc calc, int up);
void					cast_ray(t_game *game, double ray_angle, t_ray *ray);
int						load_texture(t_game *game, t_texture *tex, char *path);
int						get_tex_color(t_texture *tex, int x, int y);
int						create_color(int t, int r, int g, int b);
void					game_loop(t_game *game);
void					put_pixel(t_image *img, int x, int y, int color);
int						add_texture(t_game *game, char *line);
void					get_player_start(t_game *game);
int						add_color(t_game *game, char *line);
int						textures_colors_complete(t_game *game);
int						map_have_one_player(char **map);
int						valid_surroundings(char **map, int i, int j);
int						is_map_closed(char **map);
int						parse_map(char *path, t_game *game);
int						is_blocking_down(t_game *game, int new_x, int new_y);
int						is_blocking_up(t_game *game, int new_x, int new_y);
int						is_blocking_right(t_game *game, int new_x, int new_y);
int						is_blocking_left(t_game *game, int new_x, int new_y);
int						print_error(char *str, int exit_status);
int						is_file_extension_correct(char *filename);
int						free_game(t_game *game);
int						free_allocated_array(char ***array, int is_err);
int						free_textures(t_game *game);
void					free_partial(char ***array, int last_alloc);
int						init_tex_north(t_game *game);
int						init_tex_south(t_game *game);
int						init_tex_east(t_game *game);
int						init_tex_west(t_game *game);
int						is_player_char(char c);
int						is_map_char(char c);
int						is_map_line(char *line);
int						init_game_data(t_game *game);
int						init_map_array(t_game *game, int height, int width);
void					move_player_right(t_game *game);
void					move_player_left(t_game *game);
void					move_player_backward(t_game *game);
void					move_player_forward(t_game *game);
unsigned int			strlen_without_nl(const char *str);
char					*strdup_trimmed(const char *str);
int						string_array_length(char **array);
int						mouse_move_hook(int x, int y, t_game *game);
int						update_game(t_game *game);
void					draw_minimap(t_game *game);
int						on_focus_out(t_game *game);
int						on_focus_out(t_game *game);
void					init_hooks(t_game *game);
int						handle_focus_out(t_game *game);
int						handle_focus_in(t_game *game);
int						parse_line(char *line, t_game *game);
int						scan_map_loop(int fd, t_game *game);
int						scan_map(char *path, t_game *game);
int						key_press(int key, t_game *g);
int						key_release(int key, t_game *g);
void					update_player(t_game *g);

#endif
