/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:22:54 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/15 18:54:40 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_position(t_game *game, t_parse_state *state, int x, int y)
{
	if (state->map->player_dir)
	{
		free_resources(state->map_lines, *state->height, state->first_line);
		free(game->current_line);
		gnl_clear_stash(state->fd);
		free_all(game);
		printf("Error: multiple player start positions\n");
		exit(1);
	}
	state->map->player_x = x;
	state->map->player_y = y;
	state->map->player_dir = state->map_lines[y][x];
}

void	check_player_in_line(t_game *game, t_parse_state *state, int y)
{
	int	i;

	i = 0;
	while (state->map_lines[y][i])
	{
		if (is_player_char(state->map_lines[y][i]))
			set_player_position(game, state, i, y);
		i++;
	}
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_player_char(c));
}

void	validate_map_line(t_game *game, t_parse_state *state)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(game->current_line);
	if (len > 0 && game->current_line[len - 1] == '\n')
	{
		game->current_line[len - 1] = '\0';
	}
	while (game->current_line[++i])
	{
		if (!is_valid_map_char(game->current_line[i])
			&& game->current_line[i] != ' ' && game->current_line[i] != '\t')
		{
			printf("Error: invalid character '%c' in map\n",
				game->current_line[i]);
			free_resources(state->map_lines,
				*state->height, state->first_line);
			free_all(game);
			if (game->current_line != state->first_line)
				free(game->current_line);
			gnl_clear_stash(state->fd);
			exit(1);
		}
	}
}
