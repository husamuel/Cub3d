/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:55 by diolivei          #+#    #+#             */
/*   Updated: 2025/07/03 18:07:04 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

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

void	free_rgb_array(char **rgb, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

void	check_rgb_value(int value, char **rgb, int i)
{
	if (value < 0 || value > 255)
	{
		printf("Error: invalid RGB value\n");
		free_rgb_array(rgb, i + 1);
		exit(1);
	}
}

void	process_map_line(int fd, t_parse_state *state)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		validate_map_line(line);
		process_map(state->map_lines, state->height, line, state->max_width);
		check_player_in_line(state->map, state->map_lines[*state->height - 1],
			*state->height - 1);
		free(line);
		line = get_next_line(fd);
	}
}
