/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:22:16 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/15 19:49:09 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <ctype.h>
# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"

# define MAX_MAP_HEIGHT 1024
# define ROTATION_SPEED 0.03 // Velocidade de rotação em radianos
# define MOVE_SPEED 0.03 // Velocidade de movimentação

typedef struct s_tex
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color[3];
	int		ceiling_color[3];
	int		has_floor;
	int		has_ceiling;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int	left; // Seta esquerda (rotacionar esquerda)
	int	right; // Seta direita (rotacionar direita)
	int	forward; // Tecla W (mover para frente)
	int	backward; // Tecla S (mover para trás)
	int	strafe_left; // Tecla A (strafe à esquerda)
	int	strafe_right; // Tecla D (strafe à direita)
}	t_keys;

typedef struct s_game
{
	char		*current_line; // só para casos de erro
	void		*mlx;
	void		*win;
	void		*img;
	int			win_width;
	int			win_height;
	t_player	player;
	t_map		*map;
	t_keys		keys; // Estado das teclas
	t_tex		north;
	t_tex		south;
	t_tex		west;
	t_tex		east;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;

typedef struct s_wall
{
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_wall;

// =============== Just for norminette ====================
typedef struct s_draw_data
{
	char	*data;
	int		*info;
	t_tex	*tex;
	int		tex_x;
	int		x;
	double	step;
	double	tex_pos;
}	t_draw_data;

typedef struct s_tex_info
{
	t_game	*game;
	t_ray	*ray;
	t_wall	*wall;
	t_tex	*tex;
}	t_tex_info;

typedef struct s_parse_state
{
	t_map	*map;
	char	**map_lines;
	int		*height;
	int		*max_width;
	char	*first_line;
	int		fd;
}	t_parse_state;
// ========================================================

// Parsing functions
void	map_parser(t_game *game, char *filename);
void	parse_config_line(t_map *map, char *line, t_game *game, int fd);
void	validate_texture_paths(t_map *map, t_game *game, char *line);
void	verify_map(t_game *game);
void	check_player_in_line(t_game *game, t_parse_state *state, int y);
void	parse_config_section(t_map *map, int fd, char **line, t_game *game);
void	parse_map_grid(t_game *game, int fd, t_map *map, char *first_line);
int		check_rgb_value(int value);
void	process_map(char **map_lines, int *height, char *line, int *max_width);
int		is_player_char(char c);
int		is_valid_map_char(char c);
void	validate_map_line(t_game *game, t_parse_state *state);
void	process_map_line(t_game *game, int fd, t_parse_state *state);
int		is_line_empty(const char *line);
void	peek_ahead(t_game *game, int fd, t_parse_state *state);
void	check_row_closed(char *row, int width, t_game *game);
void	check_column_closed(t_game *game, int col);
int		count_rgb_components(char **rgb);
int		store_rgb_value(char *src, int *dest);

// Window and rendering functions (init_window.c)
int		init_window(t_game *game);
void	draw_background(t_game *game);
void	draw_walls(t_game *game);
int		init_ray(t_game *game, int x, t_ray *ray);
int		calc_step_and_dist(t_ray *ray, t_game *game);
int		perform_dda(t_game *game, t_ray *ray);
void	load_textures(t_game *game);
void	draw_texture_loop(t_draw_data *d, int draw_start, int draw_end);
int		get_tex_x(t_game *game, t_ray *ray, t_wall *wall, t_tex *tex);
void	draw_texture_column(t_tex_info *info, int x);
t_tex	*get_texture(t_game *game, t_ray *ray);
void	load_texture(t_game *game, t_tex *tex, char *path);
void	load_textures(t_game *game);

// Camera rotation functions (camera_rotation.c)
void	init_player_vectors(t_game *game);
void	rotate_camera(t_game *game, int direction);

// Key handling functions (key_handler.c)
int		loop_hook_wrapper(void *param);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	update_game(t_game *game);
int		close_window(t_game *game);

// Player movement functions (player_movement.c)
void	move_player(t_game *game);
int		check_collision(t_game *game, double new_x, double new_y);
void	set_player_direction(t_game *game);

// Game initialization and utilities
void	init_cub3d(t_game *game, char *map_file);
void	update_player(t_game *game);
int		create_trgb(int r, int g, int b);

// Debug functions
void	print_map_struct(t_map *map);
void	print_all_structs(t_game *game, t_ray *ray, t_wall *wall);

// free
void	free_all(t_game *game);
void	free_resources(char **map_lines, int height, char *line);
void	free_map_lines(char **map_lines, int height);
void	free_visited_array(char **visited, int height);
void	free_rgb_array(char **rgb, int count);
void	free_grid(t_map *map);
void	destroy_texture(void *mlx, t_tex *tex);
void	gnl_clear_stash(int fd);
char	*get_next_line(int fd);
char	*ft_strjoin1(char *s1, char *s2, int *end_loc);
void	free_and_exit(t_game *game);

#endif
