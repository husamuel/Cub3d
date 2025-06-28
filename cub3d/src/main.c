/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:34:11 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 17:38:43 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void load_texture(t_game *game, t_tex *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Erro: falha ao carregar textura '%s'\n", path);
        exit(1);
    }
    tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    if (!tex->data)
    {
        printf("Erro: falha ao obter data da textura '%s'\n", path);
        exit(1);
    }
    if (tex->height <= 0 || tex->width <= 0)
    {
        printf("Erro: textura com dimensões inválidas (%d x %d): %s\n",
               tex->width, tex->height, path);
        exit(1);
    }
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->north, game->map->no_path);
	load_texture(game, &game->south, game->map->so_path);
	load_texture(game, &game->west, game->map->we_path);
	load_texture(game, &game->east, game->map->ea_path);
}

static int	has_cub_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	return (len > 4 && ft_strcmp(filename + len - 4, ".cub") == 0);
}

static int	is_file_readable(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	validate_arguments(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Error: no .cub file provided\n");
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (argc > 2)
	{
		printf("Error: too many arguments\n");
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	return (0);
}

static int	validate_file(char *filename)
{
	if (!has_cub_extension(filename))
	{
		printf("Error: file must have .cub extension\n");
		return (1);
	}
	if (!is_file_readable(filename))
	{
		printf("Error: could not open file %s\n", filename);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (validate_arguments(argc, argv))
		return (1);
	if (validate_file(argv[1]))
		return (1);
	init_cub3d(&game, argv[1]);
	if (init_window(&game))
	{
		printf("Error: failed to initialize window\n");
		free_all(&game);
		return (1);
	}
	free_all(&game);
	return (0);
}
