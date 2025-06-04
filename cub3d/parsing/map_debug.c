/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:00:36 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:05:22 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	print_player_struct(t_player *player)
{
	printf("===== PLAYER STRUCT =====\n");
	printf("Position: x=%.2f, y=%.2f\n", player->x, player->y);
	printf("Direction: dir_x=%.2f, dir_y=%.2f\n", player->dir_x, player->dir_y);
	printf("Camera Plane: plane_x=%.2f, plane_y=%.2f\n",
		player->plane_x, player->plane_y);
}

static void	print_game_struct(t_game *game)
{
	printf("===== GAME STRUCT =====\n");
	printf("MLX: %p\n", game->mlx);
	printf("Window: %p\n", game->win);
	printf("Image: %p\n", game->img);
	printf("Window Size: width=%d, height=%d\n", game->win_width,
		game->win_height);
	printf("\n===== PLAYER =====\n");
	print_player_struct(&game->player);
	printf("\n===== MAP =====\n");
	if (game->map)
		print_map_struct(game->map);
	else
		printf("Map not initialized.\n");
}

static void	print_ray_struct(t_ray *ray)
{
	printf("===== RAY STRUCT =====\n");
	printf("Camera X: %.2f\n", ray->camera_x);
	printf("Direction: dir_x=%.2f, dir_y=%.2f\n", ray->dir_x, ray->dir_y);
	printf("Map Position: map_x=%d, map_y=%d\n", ray->map_x, ray->map_y);
	printf("Delta Dist: delta_dist_x=%.2f, delta_dist_y=%.2f\n",
		ray->delta_dist_x, ray->delta_dist_y);
	printf("Side Dist: side_dist_x=%.2f, side_dist_y=%.2f\n",
		ray->side_dist_x, ray->side_dist_y);
	printf("Step: step_x=%d, step_y=%d\n", ray->step_x, ray->step_y);
	if (ray->side == 0)
		printf("Side: %d (%s)\n", ray->side, "X");
	else
		printf("Side: %d (%s)\n", ray->side, "Y");
}

static void	print_wall_struct(t_wall *wall)
{
	printf("===== WALL STRUCT =====\n");
	printf("Perpendicular Distance: %.2f\n", wall->perp_dist);
	printf("Line Height: %d\n", wall->line_height);
	printf("Draw Start: %d\n", wall->draw_start);
	printf("Draw End: %d\n", wall->draw_end);
}

void	print_all_structs(t_game *game, t_ray *ray, t_wall *wall)
{
	printf("\n===== DEBUG ALL STRUCTS =====\n");
	print_game_struct(game);
	if (ray)
	{
		printf("\n");
		print_ray_struct(ray);
	}
	if (wall)
	{
		printf("\n");
		print_wall_struct(wall);
	}
	printf("============================\n\n");
}
