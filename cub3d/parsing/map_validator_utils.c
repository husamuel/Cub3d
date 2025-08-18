/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:06:42 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/18 14:13:06 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static void	validate_texture_path(const char *path,
	const char *label, t_game *game, char *line)
{
	if (!path)
	{
		free(line);
		free_all(game);
		printf("Error: missing texture path for %s\n", label);
		exit(1);
	}
}

void	validate_texture_paths(t_map *map, t_game *game, char *line)
{
	validate_texture_path(map->no_path, "NO", game, line);
	validate_texture_path(map->so_path, "SO", game, line);
	validate_texture_path(map->we_path, "WE", game, line);
	validate_texture_path(map->ea_path, "EA", game, line);
}

void	free_visited_array(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	count_rgb_components(char **rgb)
{
	int	count;

	count = 0;
	while (rgb[count])
		count++;
	return (count);
}

int	store_rgb_value(char *src, int *dest)
{
	int	i;

	while (*src == ' ')
		src++;
	i = ft_atoi(src);
	*dest = i;
	while (*src >= '0' && *src <= '9')
		src++;
	while (*src == ' ')
		src++;
	if (*src && *src != ',' && *src != '\n')
		return (1);
	if (check_rgb_value(i))
		return (1);
	return (0);
}
