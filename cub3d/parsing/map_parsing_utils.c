/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:55 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/15 15:52:27 by diolivei         ###   ########.fr       */
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

int	check_rgb_value(int value)
{
	if (value < 0 || value > 255 || value == '\0')
		return (1);
	return (0);
}

void	process_map_line(t_game *game, int fd, t_parse_state *state)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		game->current_line = line;
		if (is_line_empty(line))
		{
			free(line);
			peek_ahead(game, fd, state);
			game->current_line = NULL;
			return ;
		}
		validate_map_line(game, state);
		process_map(state->map_lines, state->height, line, state->max_width);
		check_player_in_line(game, state, *state->height - 1);
		free(line);
		line = get_next_line(fd);
	}
}
