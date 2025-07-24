/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:34:19 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 17:42:02 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	move_forward_backward(t_game *game, double *new_x, double *new_y)
{
	if (game->keys.forward)
	{
		*new_x += game->player.dir_x * MOVE_SPEED;
		*new_y += game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys.backward)
	{
		*new_x -= game->player.dir_x * MOVE_SPEED;
		*new_y -= game->player.dir_y * MOVE_SPEED;
	}
}

static void	move_strafe(t_game *game, double *new_x, double *new_y)
{
	double	strafe_x;
	double	strafe_y;

	strafe_x = -game->player.dir_y;
	strafe_y = game->player.dir_x;
	if (game->keys.strafe_right)
	{
		*new_x += strafe_x * MOVE_SPEED;
		*new_y += strafe_y * MOVE_SPEED;
	}
	if (game->keys.strafe_left)
	{
		*new_x -= strafe_x * MOVE_SPEED;
		*new_y -= strafe_y * MOVE_SPEED;
	}
}

int	check_collision(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->map->width
		|| map_y < 0 || map_y >= game->map->height)
		return (1);
	if (game->map->grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	move_player(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	move_forward_backward(game, &new_x, &new_y);
	move_strafe(game, &new_x, &new_y);
	if (!check_collision(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
