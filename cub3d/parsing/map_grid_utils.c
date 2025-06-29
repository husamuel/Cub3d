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

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_player_char(c));
}

void	validate_map_line(char *line)
{
	int i = 0;
	size_t len;
	
	len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
	{
        line[len - 1] = '\0';
	}
	while (line[i])
	{
		if (!is_valid_map_char(line[i]) && line[i] != ' ')
		{
			printf("Error: invalid character '%c' in map\n", line[i]);
			exit(1);
		}
		i++;
	}
}
