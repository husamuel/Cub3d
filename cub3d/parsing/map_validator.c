/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:59 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:10:46 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	flood_fill(t_map *map, char **visited, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
	{
		printf("Error: map is not closed\n");
		exit(1);
	}
	if (visited[y][x] || map->grid[y][x] == '1')
		return ;
	if (map->grid[y][x] == ' ')
	{
		printf("Error: empty space found on map\n");
		exit(1);
	}
	visited[y][x] = 1;
	flood_fill(map, visited, x + 1, y);
	flood_fill(map, visited, x - 1, y);
	flood_fill(map, visited, x, y + 1);
	flood_fill(map, visited, x, y - 1);
}

static void	check_empty_lines(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] == '\0')
		{
			printf("Error: empty line found on map\n");
			exit(1);
		}
		i++;
	}
}

static void	check_map_dimensions(t_map *map)
{
	if (!map->grid || map->height == 0 || map->width == 0)
	{
		printf("Error: empty or poorly defined map\n");
		exit(1);
	}
	if (map->height < 3 || map->width < 3)
	{
		printf("Error: very small map (minimum 3x3)\n");
		exit(1);
	}
}

static char	**allocate_visited_array(t_map *map)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * map->height);
	if (!visited)
	{
		printf("Error: memory allocation failed for visited array\n");
		exit(1);
	}
	i = -1;
	while (++i < map->height)
	{
		visited[i] = calloc(map->width, sizeof(char));
		if (!visited[i])
		{
			printf("Error: memory allocation failed for visited row\n");
			j = 0;
			while (j < i)
				free(visited[j++]);
			free(visited);
			exit(1);
		}
	}
	return (visited);
}

void	verify_map(t_map *map)
{
	char	**visited;

	check_map_dimensions(map);
	check_empty_lines(map);
	visited = allocate_visited_array(map);
	flood_fill(map, visited, map->player_x, map->player_y);
	free_visited_array(visited, map->height);
}
