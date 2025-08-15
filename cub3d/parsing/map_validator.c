/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:59 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/04 16:44:06 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	flood_fill(t_game *game, char **visited, int x, int y)
{
	t_map	*map;

	map = game->map;
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
	{
		free_visited_array(visited, map->height);
		free(game->current_line);
		free_all(game);
		printf("Error: map is not closed\n");
		exit(1);
	}
	if (visited[y][x] || map->grid[y][x] == '1')
		return ;
	if (map->grid[y][x] == ' ')
	{
		free_visited_array(visited, map->height);
		free(game->current_line);
		free_all(game);
		exit(1);
	}
	visited[y][x] = 1;
	flood_fill(game, visited, x + 1, y);
	flood_fill(game, visited, x - 1, y);
	flood_fill(game, visited, x, y + 1);
	flood_fill(game, visited, x, y - 1);
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

static void	check_spaces_in_map(t_game *game)
{
    int y;

	y = 0;
    while (y < game->map->height)
    {
        if (has_space_inside_content(game->map->grid[y], game->map->width))
        {
            printf("Error: space inside map content\n");
            free(game->current_line);
            free_all(game);
            exit(1);
        }
        y++;
    }
}

void	verify_map(t_game *game)
{
	char	**visited;

	check_map_dimensions(game->map, game, game->current_line);
	check_spaces_in_map(game);
	check_map_surrounded_by_walls(game);
	visited = allocate_visited_array(game->map);
	flood_fill(game, visited, game->map->player_x, game->map->player_y);
	free_visited_array(visited, game->map->height);
}
