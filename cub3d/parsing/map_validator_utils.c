/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:06:42 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:09:36 by diolivei         ###   ########.fr       */
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
