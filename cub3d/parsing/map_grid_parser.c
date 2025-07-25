/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:17:38 by diolivei          #+#    #+#             */
/*   Updated: 2025/07/03 18:06:36 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	allocate_grid(t_map *map, char **map_lines, int height, char *line)
{
	int	i;

	map->grid[height] = ft_strdup(map_lines[height]);
	if (!map->grid[height])
	{
		printf("Error: memory allocation failed for map grid line\n");
		i = 0;
		while (i < height)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		free_resources(map_lines, height, line);
		exit(1);
	}
}

void	allocate_grid_line(t_map *map, char **map_lines, int height, char *line)
{
	int	i;

	map->grid = malloc(sizeof(char *) * height);
	if (!map->grid)
	{
		printf("Error: memory allocation failed for map grid\n");
		free_resources(map_lines, height, line);
		exit(1);
	}
	i = 0;
	while (i < height)
	{
		allocate_grid(map, map_lines, i, line);
		i++;
	}
}

void	process_map(char **map_lines, int *height, char *line, int *max_width)
{
	int		width;
	char	*newline;

	newline = ft_strchr(line, '\n');
	if (newline)
		*newline = '\0';
	map_lines[*height] = ft_strdup(line);
	if (!map_lines[*height])
	{
		printf("Error: memory allocation failed for map line\n");
		free_map_lines(map_lines, *height);
		free(line);
		exit(1);
	}
	width = ft_strlen(map_lines[*height]);
	if (width > *max_width)
		*max_width = width;
	(*height)++;
}

static int	process_first_line(t_game *game, t_map *map, char **map_lines, int *height, char *first_line)
{
	int		width;
	char	*newline;

	if (!first_line)
		return (0);
	newline = ft_strchr(first_line, '\n');
	if (newline)
		*newline = '\0';
	map_lines[0] = ft_strdup(first_line);
	if (!map_lines[0])
	{
		printf("Error: memory allocation failed for map line\n");
		exit(1);
	}
	width = ft_strlen(map_lines[0]);
	check_player_in_line(game, map, map_lines[0], 0, map_lines, height, first_line);
	return (width);
}

void	parse_map_grid(t_game *game, int fd, t_map *map, char *first_line)
{
	char			*map_lines[MAX_MAP_HEIGHT];
	int				height;
	int				max_width;
	t_parse_state	state;

	height = 0;
	max_width = process_first_line(game, map, map_lines, &height, first_line);
	if (max_width == 0)
	{
		height = 0;
		max_width = 0;
	}
	else
		height = 1;
	state = (t_parse_state){map, map_lines, &height, &max_width};
	process_map_line(game, fd, &state, first_line);
	map->height = height;
	map->width = max_width;
	allocate_grid_line(map, map_lines, height, NULL);
	free_resources(map_lines, height, NULL);
}
