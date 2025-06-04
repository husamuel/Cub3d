/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:34:24 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:57:39 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	process_player_found(t_game *game, int x, int y)
{
	game->map->player_x = x;
	game->map->player_y = y;
	game->map->player_dir = game->map->grid[y][x];
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	set_player_direction(game);
	game->map->grid[y][x] = '0';
}

void	update_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width && game->map->grid[y][x])
		{
			if (ft_strchr("NSEW", game->map->grid[y][x]))
			{
				process_player_found(game, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
	printf("Error: No player found in map\n");
	exit(1);
}
