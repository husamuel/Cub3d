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

static void	flood_fill(t_game *game, t_map *map, char **visited, int x, int y, char *line)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
	{
		free_visited_array(visited, map->height);
		free(line);
		free_all(game);
		printf("Error: map is not closed\n");
		exit(1);
	}
	if (visited[y][x] || map->grid[y][x] == '1')
		return ;
	if (map->grid[y][x] == ' ')
	{
		free_visited_array(visited, map->height);
		free(line);
		free_all(game);
		printf("Error: empty space found on map\n");
		exit(1);
	}
	visited[y][x] = 1;
	flood_fill(game, map, visited, x + 1, y, line);
	flood_fill(game, map, visited, x - 1, y, line);
	flood_fill(game, map, visited, x, y + 1, line);
	flood_fill(game, map, visited, x, y - 1, line);
}

static void	check_empty_lines(t_map *map, t_game *game, char *line)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] == '\0')
		{
			free(line);
			free_all(game);
			printf("Error: empty line found on map\n");
			exit(1);
		}
		i++;
	}
}

static void	check_map_dimensions(t_map *map, t_game *game, char *line)
{
	if (!map->grid || map->height == 0 || map->width == 0)
	{
		free(line);
		free_all(game);
		printf("Error: empty or poorly defined map\n");
		exit(1);
	}
	if (map->height < 3 || map->width < 3)
	{
		free(line);
		free_all(game);
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

void	verify_map(t_game *game, t_map *map, char *line)
{
	char	**visited;

	check_map_dimensions(map, game, line);
	check_empty_lines(map, game, line);
	visited = allocate_visited_array(map);
	flood_fill(game, map, visited, map->player_x, map->player_y, line);
	free_visited_array(visited, map->height);
}
