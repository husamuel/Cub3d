/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:51 by diolivei          #+#    #+#             */
/*   Updated: 2025/08/04 17:48:19 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	check_file_open(int fd, char *filename)
{
	if (fd < 0)
	{
		printf("Error: cannot open file %s\n", filename);
		exit(1);
	}
}

void	check_config_complete(t_map *map, char *line, int fd, t_game *game)
{
	if (!map->has_floor || !map->has_ceiling)
	{
		printf("Error: incomplete configuration\n");
		free(line);
		gnl_clear_stash(fd);
		close(fd);
		free_all(game);
		exit(1);
	}
}

void	skip_empty_lines(int fd, char **line)
{
	*line = get_next_line(fd);
	while (*line)
	{
		if ((*line)[0] != '\n' && (*line)[0] != '\0')
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
}

void	parse_config_section(t_map *map, int fd, char **line, t_game *game)
{
	int		config_count;

	config_count = 0;
	while (config_count < 6)
	{
		*line = get_next_line(fd);
		if (!*line)
			break ;
		if ((*line)[0] == '\n' || (*line)[0] == '\0')
		{
			free(*line);
			continue ;
		}
		parse_config_line(map, *line, game, fd);
		config_count++;
		free(*line);
	}
	skip_empty_lines(fd, line);
}

void	map_parser(t_game *game, char *filename)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(filename, O_RDONLY);
	check_file_open(fd, filename);
	parse_config_section(game->map, fd, &line, game);
	check_config_complete(game->map, line, fd, game);
	parse_map_grid(game, fd, game->map, line);
	validate_texture_paths(game->map, game, line);
	game->current_line = line;
	verify_map(game);
	free(line);
	gnl_clear_stash(fd);
	close(fd);
}
