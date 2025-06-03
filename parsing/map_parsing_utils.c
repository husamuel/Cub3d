#include "./../cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_position(t_map *map, int x, int y, char dir)
{
	if (map->player_dir)
	{
		printf("Error: multiple player start positions\n");
		exit(1);
	}
	map->player_x = x;
	map->player_y = y;
	map->player_dir = dir;
}

void	check_player_in_line(t_map *map, char *line, int y)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_player_char(line[i]))
			set_player_position(map, i, y, line[i]);
		i++;
	}
}

void	free_map_lines(char **map_lines, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_lines[i]);
		i++;
	}
}

void	free_resources(char **map_lines, int height, char *line)
{
	free_map_lines(map_lines, height);
	free(line);
}
