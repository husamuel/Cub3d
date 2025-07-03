/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:33:51 by diolivei          #+#    #+#             */
/*   Updated: 2025/07/03 18:27:24 by diolivei         ###   ########.fr       */
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
