/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:22:54 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:52:47 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	handle_map_line(t_map *map, char *line, t_grid_info *info)
{
	if (line[0] == '\n')
		return ;
	process_map(info->map_lines, info->height, line, info->max_width);
	check_player_in_line(map, info->map_lines[*info->height], *info->height);
	(*info->height)++;
	if (*info->height >= MAX_MAP_HEIGHT)
	{
		printf("Error: map too tall\n");
		free_resources(info->map_lines, *info->height, line);
		exit(1);
	}
}

void	read_map_lines(FILE *file, t_map *map, t_grid_info *info)
{
	char	*line;
	size_t	len;
	ssize_t	read;

	line = NULL;
	len = 0;
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (read > 1 && line[0] != '\n')
			handle_map_line(map, line, info);
	}
	free(line);
}
