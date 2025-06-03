#include "./cub3d.h"

static int	init_ray(t_game *game, int x, t_ray *ray)
{
	if (!game || !game->map || !game->map->grid)
		return (0);
	ray->camera_x = 2 * x / (double)game->win_width - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	return (1);
}

static int	set_x_dir(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	return (1);
}

static int	set_y_dir(t_ray *ray, t_game *game)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
	return (1);
}

static int	calc_step_and_dist(t_ray *ray, t_game *game)
{
	if (ray->dir_x == 0 || ray->dir_y == 0)
		return (0);
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	set_x_dir(ray, game);
	set_y_dir(ray, game);
	return (1);
}

static int	is_out_of_bounds(t_game *game, t_ray *ray)
{
	return (ray->map_x < 0 || ray->map_x >= game->map->width
		|| ray->map_y < 0 || ray->map_y >= game->map->height);
}

static int	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_out_of_bounds(game, ray))
			return (0);
		if (game->map->grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (1);
}

static void	set_wall_draw_limits(t_wall *wall, int win_height)
{
	wall->draw_start = -wall->line_height / 2 + win_height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + win_height / 2;
	if (wall->draw_end >= win_height)
		wall->draw_end = win_height - 1;
}

static int	calc_wall_dist_and_height(t_game *game, t_ray *ray, t_wall *wall)
{
	if (ray->side == 0)
		wall->perp_dist = (ray->map_x - game->player.x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		wall->perp_dist = (ray->map_y - game->player.y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	if (wall->perp_dist <= 0)
		return (0);
	wall->line_height = (int)(game->win_height / wall->perp_dist);
	set_wall_draw_limits(wall, game->win_height);
	return (1);
}

static void	draw_wall_column(t_game *game, t_ray *ray, t_wall *wall, int x)
{
	int		y;
	char	*dst;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		color;

	if (!game || !game->img)
		return ;
	data = mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
	if (ray->side == 0)
		color = create_trgb(255, 0, 0);
	else
		color = create_trgb(128, 0, 0);
	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		dst = data + (y * size_line + x * (bpp / 8));
		*(unsigned int *)dst = color;
		y++;
	}
}

static int	cast_ray(t_game *game, int x, t_ray *ray, t_wall *wall)
{
	if (!init_ray(game, x, ray))
		return (0);
	if (!calc_step_and_dist(ray, game))
		return (0);
	if (!perform_dda(game, ray))
		return (0);
	if (!calc_wall_dist_and_height(game, ray, wall))
		return (0);
	return (1);
}

void	draw_walls(t_game *game)
{
	int		x;
	t_ray	ray;
	t_wall	wall;

	if (!game || !game->img || !game->map || game->win_width <= 0)
		return ;
	x = 0;
	while (x < game->win_width)
	{
		if (!cast_ray(game, x, &ray, &wall))
		{
			if (x == 0)
				print_all_structs(game, &ray, &wall);
			x++;
			continue ;
		}
		draw_wall_column(game, &ray, &wall, x);
		x++;
	}
}