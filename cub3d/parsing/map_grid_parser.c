/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:17:38 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:53:44 by diolivei         ###   ########.fr       */
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
	char	*newline = ft_strchr(line, '\n');

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

static int	process_first_line(t_map *map, char **map_lines, char *first_line)
{
	int		width;
	char	*newline = ft_strchr(first_line, '\n');

	if (newline)
		*newline = '\0';
	map_lines[0] = ft_strdup(first_line);
	if (!map_lines[0])
	{
		printf("Error: memory allocation failed for map line\n");
		exit(1);
	}
	width = ft_strlen(map_lines[0]);
	check_player_in_line(map, map_lines[0], 0);
	return (width);
}

void	parse_map_grid(int fd, t_map *map, char *first_line)
{
	char		*map_lines[MAX_MAP_HEIGHT];
	int			height;
	int			max_width;
	char		*line;

	height = 0;
	max_width = process_first_line(map, map_lines, first_line);
	height++;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		validate_map_line(line);
		process_map(map_lines, &height, line, &max_width);
		check_player_in_line(map, map_lines[height - 1], height - 1);
		free(line);
	}
	map->height = height;
	map->width = max_width;
	allocate_grid_line(map, map_lines, height, NULL);
	free_resources(map_lines, height, NULL);
}
