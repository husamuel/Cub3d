#include "./../cub3d.h"

static void	allocate_grid_line(t_map *map, char **map_lines, int height, char *line)
{
	int	i;

	map->grid[height] = strdup(map_lines[height]);
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

static void	allocate_grid(t_map *map, char **map_lines, int height, char *line)
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
		allocate_grid_line(map, map_lines, i, line);
		i++;
	}
}

static void	process_map_line(char **map_lines, int *height, char *line,
	int *max_width)
{
	int	width;

	line[strcspn(line, "\n")] = 0;
	map_lines[*height] = strdup(line);
	if (!map_lines[*height])
	{
		printf("Error: memory allocation failed for map line\n");
		free_map_lines(map_lines, *height);
		free(line);
		exit(1);
	}
	width = strlen(map_lines[*height]);
	if (width > *max_width)
		*max_width = width;
}

static int	process_first_line(t_map *map, char **map_lines, char *first_line)
{
	int	width;
	int	max_width;

	first_line[strcspn(first_line, "\n")] = 0;
	map_lines[0] = strdup(first_line);
	if (!map_lines[0])
	{
		printf("Error: memory allocation failed for map line\n");
		exit(1);
	}
	width = strlen(map_lines[0]);
	max_width = width;
	check_player_in_line(map, map_lines[0], 0);
	return (max_width);
}

void	parse_map_grid(FILE *file, t_map *map, char *first_line)
{
	char	*line;
	size_t	len;
	ssize_t	read;
	char	*map_lines[MAX_MAP_HEIGHT];
	int		height;
	int		max_width;

	line = NULL;
	len = 0;
	height = 0;
	max_width = process_first_line(map, map_lines, first_line);
	height++;
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (read <= 1 || line[0] == '\n')
			continue ;
		process_map_line(map_lines, &height, line, &max_width);
		check_player_in_line(map, map_lines[height], height);
		height++;
		if (height >= MAX_MAP_HEIGHT)
		{
			printf("Error: map too tall\n");
			free_resources(map_lines, height, line);
			exit(1);
		}
	}
	map->height = height;
	map->width = max_width;
	allocate_grid(map, map_lines, height, line);
	free_resources(map_lines, height, line);
}