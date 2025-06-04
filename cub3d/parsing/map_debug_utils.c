/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:56:30 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:01:49 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	print_texture_paths(t_map *map)
{
	printf("===== TEXTURE PATHS =====\n");
	if (map->no_path)
		printf("NO: %s\n", map->no_path);
	else
		printf("NO: NULL\n");
	if (map->so_path)
		printf("SO: %s\n", map->so_path);
	else
		printf("SO: NULL\n");
	if (map->we_path)
		printf("WE: %s\n", map->we_path);
	else
		printf("WE: NULL\n");
	if (map->ea_path)
		printf("EA: %s\n", map->ea_path);
	else
		printf("EA: NULL\n");
}

static void	print_colors(t_map *map)
{
	printf("\n===== COLORS =====\n");
	printf("Floor:   R:%d G:%d B:%d\n", map->floor_color[0],
		map->floor_color[1], map->floor_color[2]);
	printf("Ceiling: R:%d G:%d B:%d\n", map->ceiling_color[0],
		map->ceiling_color[1], map->ceiling_color[2]);
}

static void	print_player_info(t_map *map)
{
	printf("\n===== PLAYER INFO =====\n");
	printf("Position: (%d, %d)\n", map->player_x, map->player_y);
	printf("Direction: %c\n", map->player_dir);
}

static void	print_map_grid(t_map *map)
{
	int	i;

	i = 0;
	printf("\n===== MAP GRID =====\n");
	printf("Width: %d, Height: %d\n", map->width, map->height);
	if (map->grid && map->height > 0)
	{
		while (i < map->height)
		{
			if (map->grid[i])
				printf("[%2d]: %s\n", i, map->grid[i]);
			else
				printf("[%2d]: NULL\n", i);
			i++;
		}
	}
	else
		printf("Map grid not loaded.\n");
}

void	print_map_struct(t_map *map)
{
	print_texture_paths(map);
	print_colors(map);
	print_player_info(map);
	print_map_grid(map);
}
