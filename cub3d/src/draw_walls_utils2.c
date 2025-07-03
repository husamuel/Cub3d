/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:18:00 by diolivei          #+#    #+#             */
/*   Updated: 2025/07/03 18:34:33 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	draw_texture_loop(t_draw_data *d, int draw_start, int draw_end)
{
	int	y;
	int	tex_y;
	int	color;

	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)(d->tex_pos) % d->tex->height;
		color = ((unsigned int *)d->tex->data)
		[tex_y * d->tex->width + d->tex_x];
		*(unsigned int *)(d->data
				+ (y * d->info[1] + d->x * (d->info[0] / 8))) = color;
		d->tex_pos += d->step;
		y++;
	}
}

int	get_tex_x(t_game *game, t_ray *ray, t_wall *wall, t_tex *tex)
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

void	draw_texture_column(t_tex_info *info, int x)
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

t_tex	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0)
		return (&game->south);
	else if (ray->side == 0 && ray->dir_x < 0)
		return (&game->north);
	else if (ray->side == 1 && ray->dir_y > 0)
		return (&game->east);
	return (&game->west);
}
