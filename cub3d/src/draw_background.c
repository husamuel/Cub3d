/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:33:46 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:37:56 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

int	create_trgb(int r, int g, int b)
{
	int	color;

	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	return (color);
}

static int	get_ceiling_color(t_game *game)
{
	return (create_trgb(game->map->ceiling_color[0],
			game->map->ceiling_color[1], game->map->ceiling_color[2]));
}

static int	get_floor_color(t_game *game)
{
	return (create_trgb(game->map->floor_color[0],
			game->map->floor_color[1], game->map->floor_color[2]));
}

static void	draw_line_pixels(t_game *game, char *data, int y, int color)
{
	int		x;
	char	*dst;
	int		bpp;
	int		size_line;
	int		endian;

	mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
	x = 0;
	while (x < game->win_width)
	{
		dst = data + (y * size_line + x * (bpp / 8));
		*(unsigned int *)dst = color;
		x++;
	}
}

// info[0] = bpp, info[1] = size_line, info[2] = endian
void	draw_background(t_game *game)
{
	int		y;
	int		color;
	char	*data;
	int		info[3];

	if (!game->img || !game->map)
		return ;
	data = mlx_get_data_addr(game->img, &info[0], &info[1], &info[2]);
	y = 0;
	while (y < game->win_height)
	{
		if (y < game->win_height / 2)
			color = get_ceiling_color(game);
		else
			color = get_floor_color(game);
		draw_line_pixels(game, data, y, color);
		y++;
	}
}
