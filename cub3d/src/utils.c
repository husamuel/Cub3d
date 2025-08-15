/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:34:27 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/04 17:11:11 by diolivei         ###   ########.fr       */
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

int	has_space_inside_content(char *line, int width)
{
    int start = 0;
    int end = width - 1;
    int x;

    while (start < width && line[start] == ' ')
        start++;
    while (end >= 0 && line[end] == ' ')
        end--;
    x = start;
    while (x <= end)
    {
        if (line[x] == ' ')
            return (1);
        x++;
    }
    return (0);
}

void	check_map_surrounded_by_walls(t_game *game)
{
    int x;
	int y;

    y = -1;
    while (++y < game->map->width)
    {
        if (game->map->grid[0][y] != '1' || game->map->grid[game->map->height - 1][y] != '1')
        {
            printf("Error: map is not surrounded by walls\n");
			free(game->current_line);
			free_all(game);
            exit(1);
        }
    }
    x = -1;
    while (++x < game->map->height)
    {
        if (game->map->grid[x][0] != '1' || game->map->grid[x][game->map->width - 1] != '1')
        {
            printf("Error: map is not surrounded by walls\n");
			free(game->current_line);
			free_all(game);
            exit(1);
        }
    }
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
