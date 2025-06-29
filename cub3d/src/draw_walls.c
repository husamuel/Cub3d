/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:33:51 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 19:07:42 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

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

static void	draw_texture_loop(t_draw_data *d, int draw_start, int draw_end)
{
	int	y;
	int	tex_y;
	int	color;

	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)(d->tex_pos) % d->tex->height;
		color = ((unsigned int *)d->tex->data)[tex_y * d->tex->width + d->tex_x];
		*(unsigned int *)(d->data + (y * d->info[1] + d->x * (d->info[0] / 8))) = color;
		d->tex_pos += d->step;
		y++;
	}
}

static int	get_tex_x(t_game *game, t_ray *ray, t_wall *wall, t_tex *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.y + wall->perp_dist * ray->dir_y;
	else
		wall_x = game->player.x + wall->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)(tex->width));
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_texture_column(t_tex_info *info, int x)
{
	int				mlx_info[3];
	t_draw_data		d;

	d.data = mlx_get_data_addr(info->game->img,
			&mlx_info[0], &mlx_info[1], &mlx_info[2]);
	d.info = mlx_info;
	d.tex = info->tex;
	d.tex_x = get_tex_x(info->game, info->ray, info->wall, info->tex);
	d.x = x;
	d.step = 1.0 * d.tex->height / info->wall->line_height;
	d.tex_pos = (info->wall->draw_start - info->game->win_height / 2
			+ info->wall->line_height / 2) * d.step;
	draw_texture_loop(&d, info->wall->draw_start, info->wall->draw_end);
}

static t_tex *get_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0 && ray->dir_x > 0)
        return (&game->south);  // swapped here
    else if (ray->side == 0 && ray->dir_x < 0)
        return (&game->north);  // swapped here
    else if (ray->side == 1 && ray->dir_y > 0)
        return (&game->east);
    return (&game->west);
}

void	draw_wall_column(t_game *game, t_ray *ray, t_wall *wall, int x)
{
	t_tex		*tex;
	t_tex_info	info;

	if (!game || !game->img)
		return ;
	tex = get_texture(game, ray);
	info.game = game;
	info.ray = ray;
	info.wall = wall;
	info.tex = tex;
	draw_texture_column(&info, x);
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
