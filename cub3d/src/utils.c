/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:34:27 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/15 19:48:40 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

char	*ft_strjoin1(char *s1, char *s2, int *end_loc)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(result, s1, len1);
	free(s1);
	ft_memcpy(result + len1, s2, len2 + 1);
	if (len1 + len2 > 0 && *(result + len1 + len2 - 1) == '\n')
		*end_loc = 0;
	return (result);
}

int	is_line_empty(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

void	check_row_closed(char *row, int width, t_game *game)
{
	int	start;
	int	end;

	start = 0;
	end = width - 1;
	while (start < width && (row[start] == ' ' || row[start] == '\t'))
		start++;
	while (end >= 0 && (row[end] == ' ' || row[end] == '\t'))
		end--;
	if (start > end || row[start] != '1' || row[end] != '1')
		free_and_exit(game);
}

void	check_column_closed(t_game *game, int col)
{
	int	start;
	int	end;

	start = 0;
	end = game->map->height - 1;
	while (start < game->map->height
		&& (game->map->grid[start][col] == ' '
		|| game->map->grid[start][col] == '\t'))
		start++;
	while (end >= 0 && (game->map->grid[end][col] == ' '
		|| game->map->grid[end][col] == '\t'))
		end--;
	if (start > end || game->map->grid[start][col] != '1'
		|| game->map->grid[end][col] != '1')
		free_and_exit(game);
}

void	peek_ahead(t_game *game, int fd, t_parse_state *state)
{
	char	*next;

	next = get_next_line(fd);
	while (next)
	{
		if (!is_line_empty(next))
		{
			free(next);
			printf("Error: empty line found on map\n");
			free_resources(state->map_lines, *state->height, state->first_line);
			free_all(game);
			gnl_clear_stash(fd);
			exit(1);
		}
		free(next);
		next = get_next_line(fd);
	}
}
