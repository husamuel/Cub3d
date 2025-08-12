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

static void	parse_color(int *dest, char *line, t_game *game, int fd)
{
	char	**rgb;
	int		i;
	int		comp_count;

	rgb = split_color(line + 2);
	comp_count = 0;
	i = -1;
	while (rgb[comp_count])
		comp_count++;
	if (comp_count != 3)
	{
		printf("Error: invalid number of RGB components\n");
		free_rgb_array(rgb, comp_count);
		free(line);
		gnl_clear_stash(fd);
		free_all(game);
		exit(1);
	}
	while (++i < 3)
	{
		dest[i] = ft_atoi(rgb[i]);
		game->current_line = line;
		check_rgb_value(dest[i], rgb, game, fd);
	}
	free_rgb_array(rgb, 3);
}

int	store_texture_path(char **dest, char *src)
{
	int		i;

	if (*dest)
	{
		free(*dest);
		*dest = NULL;
	}
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
	src += i;
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
