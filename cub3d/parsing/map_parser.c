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

static void	check_file_open(int fd, char *filename)
{
	if (fd < 0)
	{
		printf("Error: cannot open file %s\n", filename);
		exit(1);
	}
}

static FILE	*convert_fd_to_file(int fd)
{
	FILE	*file;

	file = fdopen(fd, "r");
	if (!file)
	{
		printf("Error: cannot convert file descriptor to FILE stream\n");
		close(fd);
		exit(1);
	}
	return (file);
}

static void	check_config_complete(int config_count, char *line, FILE *file)
{
	if (config_count < 6)
	{
		printf("Error: incomplete configuration\n");
		free(line);
		fclose(file);
		exit(1);
	}
}

int	parse_config_section(t_map *map, FILE *file, char **line)
{
	size_t	len;
	ssize_t	read;
	int		config_count;

	len = 0;
	config_count = 0;
	while (config_count < 6 && (read = getline(line, &len, file)) != -1)
	{
		if (read <= 1 || (*line)[0] == '\n')
			continue ;
		(*line)[strcspn(*line, "\n")] = 0;
		parse_config_line(map, *line);
		config_count++;
	}
	return (config_count);
}

void	map_parser(t_game *game, char *filename)
{
	int		fd;
	FILE	*file;
	char	*line;
	int		config_count;

	fd = open(filename, O_RDONLY);
	check_file_open(fd, filename);
	file = convert_fd_to_file(fd);
	line = NULL;
	config_count = parse_config_section(game->map, file, &line);
	check_config_complete(config_count, line, file);
	parse_map_grid(file, game->map, line);
	validate_texture_paths(game->map);
	verify_map(game->map);
	free(line);
	fclose(file);
}
