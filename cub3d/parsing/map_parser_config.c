/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:46 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/12 18:44:00 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

static int	parse_color_values(char *src, int *dest)
{
	char	**rgb;
	int		i;

	rgb = ft_split(src, ',');
	if (!rgb)
	{
		printf("Error: memory allocation failed for RGB split\n");
		exit(1);
	}
	if (count_rgb_components(rgb) != 3)
	{
		free_rgb_array(rgb, count_rgb_components(rgb));
		return (1);
	}
	i = -1;
	while (++i < 3)
		if (store_rgb_value(rgb[i], &dest[i]))
		{
			free_rgb_array(rgb, 3);
			return (1);
		}
	free_rgb_array(rgb, 3);
	return (0);
}

static void parse_color(int *dest, char *line, t_game *game, int fd)
{
	int	flag;

	line += 2;
	while (*line == ' ')
		line++;
	flag = parse_color_values(line, dest);
	while (*line && *line != '\n')
		line++;
	while (*line == ' ' || *line == '\n')
		line++;
	if (flag || *line != '\0')
	{
		printf("Error: extra characters in RGB config\n");
		free(game->current_line);
		gnl_clear_stash(fd);
		free_all(game);
		exit(1);
	}
}

int	store_texture_path(char **dest, char *src)
{
	int	i;

	while (*src == ' ')
		src++;
	if (*dest)
		free(*dest);
	*dest = ft_strdup(src);
	if (!*dest)
	{
		printf("Error: memory allocation failed for path\n");
		exit(1);
	}
	i = ft_strlen(*dest) - 1;
	while (i >= 0 && ((*dest)[i] == ' ' || (*dest)[i] == '\n'))
		i--;
	(*dest)[i + 1] = '\0';
	while (*src && *src != '\n' && *src != ' ')
		src++;
	while (*src == ' ' || *src == '\n')
		src++;
	if (*src != '\0')
		return (1);
	return (0);
}

static void	parse_texture(t_game *game, char *line, int type, int fd)
{
	int	flag;

	flag = 0;
	while (*line == ' ')
		line++;
	if (type == 0)
		flag = store_texture_path(&game->map->no_path, line + 3);
	else if (type == 1)
		flag = store_texture_path(&game->map->so_path, line + 3);
	else if (type == 2)
		flag = store_texture_path(&game->map->we_path, line + 3);
	else if (type == 3)
		flag = store_texture_path(&game->map->ea_path, line + 3);
	if (flag)
	{
		printf("Error: extra characters in texture config\n");
		free(line);
		gnl_clear_stash(fd);
		free_all(game);
		exit(1);
	}
}

void	parse_config_line(t_map *map, char *line, t_game *game, int fd)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		parse_texture(game, line, 0, fd);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		parse_texture(game, line, 1, fd);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		parse_texture(game, line, 2, fd);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		parse_texture(game, line, 3, fd);
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		parse_color(map->floor_color, line, game, fd);
		map->has_floor = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		parse_color(map->ceiling_color, line, game, fd);
		map->has_ceiling = 1;
	}
}
