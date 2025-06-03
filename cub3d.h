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
# define MOVE_SPEED 0.03      // Velocidade de movimentação

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
# if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     player_x;
    int     player_y;
    char    player_dir;
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    int     floor_color[3];
    int     ceiling_color[3];
} t_map;

typedef struct s_player
{
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
} t_player;

typedef struct s_keys
{
    int left;         // Seta esquerda (rotacionar esquerda)
    int right;        // Seta direita (rotacionar direita)
    int forward;      // Tecla W (mover para frente)
    int backward;     // Tecla S (mover para trás)
    int strafe_left;  // Tecla A (strafe à esquerda)
    int strafe_right; // Tecla D (strafe à direita)
} t_keys;

typedef struct s_game
{
    void      *mlx;
    void      *win;
    void      *img;
    int       win_width;
    int       win_height;
    t_player  player;
    t_map     *map;
    t_keys    keys; // Estado das teclas
} t_game;

typedef struct s_ray
{
    double  camera_x;
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  side_dist_x;
    double  side_dist_y;
    int     step_x;
    int     step_y;
    int     side;
} t_ray;

typedef struct s_wall
{
    double  perp_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;
} t_wall;

// Parsing functions (map_parsing_config.c, parse_map.c, parse_utils.c, validate_map.c)
void map_parser(t_game *game, char *filename);
void parse_config_line(t_map *map, char *line);
void validate_texture_paths(t_map *map);
void verify_map(t_map *map);
void	check_player_in_line(t_map *map, char *line, int y);
int	parse_config_section(t_map *map, FILE *file, char **line);
void	parse_map_grid(FILE *file, t_map *map, char *first_line);
// Window and rendering functions (init_window.c)
int init_window(t_game *game);
void draw_background(t_game *game);
void draw_walls(t_game *game);

// Camera rotation functions (camera_rotation.c)
void init_player_vectors(t_game *game);
void rotate_camera(t_game *game, int direction);

// Key handling functions (key_handler.c)
int loop_hook_wrapper(void *param);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
void update_game(t_game *game);
int close_window(t_game *game);

// Player movement functions (player_movement.c)
void move_player(t_game *game);
int check_collision(t_game *game, double new_x, double new_y);

// Game initialization and utilities
void init_cub3d(t_game *game, char *map_file);
void update_player(t_game *game);
int create_trgb(int r, int g, int b);

// Debug functions
void print_all_structs(t_game *game, t_ray *ray, t_wall *wall);

// free
void    free_all(t_game *game);
void	free_resources(char **map_lines, int height, char *line);
void	free_map_lines(char **map_lines, int height);

char	*get_next_line(int fd);
char	*ft_strjoin1(char *s1, char *s2, int *end_loc);

#endif