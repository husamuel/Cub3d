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

static void draw_wall_column(t_game *game, t_ray *ray, t_wall *wall, int x)
{
    int y;
    char *dst;
    char *data;
    int info[3];
    t_tex *tex;
    int tex_x;
    int tex_y;
    int color;
    double step;
    double tex_pos;
    double wall_x;

    if (!game || !game->img)
        return;
    data = mlx_get_data_addr(game->img, &info[0], &info[1], &info[2]);
    if (ray->side == 0 && ray->dir_x > 0)
        tex = &game->west;
    else if (ray->side == 0 && ray->dir_x < 0)
        tex = &game->east;
    else if (ray->side == 1 && ray->dir_y > 0)
        tex = &game->north;
    else
        tex = &game->south;
    if (ray->side == 0)
        wall_x = game->player.y + wall->perp_dist * ray->dir_y;
    else
        wall_x = game->player.x + wall->perp_dist * ray->dir_x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)(tex->width));
    if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
        tex_x = tex->width - tex_x - 1;
    step = 1.0 * tex->height / wall->line_height;
    tex_pos = (wall->draw_start - game->win_height / 2 + wall->line_height / 2) * step;
    y = wall->draw_start;
    while (y <= wall->draw_end)
    {
        tex_y = (int)tex_pos % tex->height;
        tex_pos += step;
        color = ((unsigned int *)tex->data)[tex_y * tex->width + tex_x];
        dst = data + (y * info[1] + x * (info[0] / 8));
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
