/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:33:35 by diolivei          #+#    #+#             */
/*   Updated: 2025/07/03 18:33:45 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

void	load_texture(t_game *game, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		printf("Erro: falha ao carregar textura '%s'\n", path);
		free_all(game);
		exit(1);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->data)
	{
		printf("Erro: falha ao obter data da textura '%s'\n", path);
		free_all(game);
		exit(1);
	}
	if (tex->height <= 0 || tex->width <= 0)
	{
		printf("Erro: textura com dimensões inválidas (%d x %d): %s\n",
			tex->width, tex->height, path);
		free_all(game);
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
