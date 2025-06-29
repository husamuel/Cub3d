/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:46 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:32:45 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static char	**split_color(char *line)
{
	char	**result;

	result = ft_split(line, ',');
	if (!result)
	{
		printf("Error: memory allocation failed for RGB split\n");
		exit(1);
	}
	return (result);
}

static void	parse_color(int *dest, char *line)
{
	char	**rgb;
	int		i;

	rgb = split_color(line);
	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
		{
			printf("Error: missing RGB component\n");
			free_rgb_array(rgb, i);
			exit(1);
		}
		dest[i] = ft_atoi(rgb[i]);
		check_rgb_value(dest[i], rgb, i);
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

static void	store_texture_path(char **dest, char *src)
{
	int		i;

	*dest = ft_strdup(src);
	if (!*dest)
	{
		printf("Error: memory allocation failed for path\n");
		exit(1);
	}
	i = 0;
	while ((*dest)[i] && (*dest)[i] != '\n' && (*dest)[i] != ' ')
		i++;
	(*dest)[i] = '\0';
}

static void	parse_texture(t_map *map, char *line, int type)
{
	while (*line == ' ')
		line++;
	if (type == 0)
		store_texture_path(&map->no_path, line + 3);
	else if (type == 1)
		store_texture_path(&map->so_path, line + 3);
	else if (type == 2)
		store_texture_path(&map->we_path, line + 3);
	else if (type == 3)
		store_texture_path(&map->ea_path, line + 3);
}

void	parse_config_line(t_map *map, char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(map, line, 0);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(map, line, 1);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(map, line, 2);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(map, line, 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(map->floor_color, line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(map->ceiling_color, line + 2);
}
