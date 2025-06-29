/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:28:51 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 18:52:36 by diolivei         ###   ########.fr       */
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

void	check_config_complete(int config_count, char *line, int fd)
{
	if (config_count < 6)
	{
		printf("Error: incomplete configuration\n");
		free(line);
		close(fd);
		exit(1);
	}
}

int	parse_config_section(t_map *map, int fd, char **line)
{
	int		config_count;

	config_count = 0;
	while (config_count < 6)
	{
		*line = get_next_line(fd);
		if (!*line)
			break;
		if ((*line)[0] == '\n' || (*line)[0] == '\0')
		{
			free(*line);
			continue;
		}
		parse_config_line(map, *line);
		config_count++;
		free(*line);
	}
	while ((*line = get_next_line(fd)))
	{
		if ((*line)[0] != '\n' && (*line)[0] != '\0')
			break;
		free(*line);
	}
	return (config_count);
}

void	map_parser(t_game *game, char *filename)
{
	int		fd;
	char	*line = NULL;
	int		config_count;

	fd = open(filename, O_RDONLY);
	check_file_open(fd, filename);
	config_count = parse_config_section(game->map, fd, &line);
	check_config_complete(config_count, line, fd);
	parse_map_grid(fd, game->map, line);
	validate_texture_paths(game->map);
	verify_map(game->map);
	free(line);
	close(fd);
}
