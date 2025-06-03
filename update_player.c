#include "cub3d.h"

static void	set_player_direction(t_game *game)
{
	if (game->map->player_dir == 'N')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (game->map->player_dir == 'S')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
	else if (game->map->player_dir == 'E')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (game->map->player_dir == 'W')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
}

static void	process_player_found(t_game *game, int x, int y)
{
	game->map->player_x = x;
	game->map->player_y = y;
	game->map->player_dir = game->map->grid[y][x];
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	set_player_direction(game);
	game->map->grid[y][x] = '0';
}

void	update_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width && game->map->grid[y][x])
		{
			if (ft_strchr("NSEW", game->map->grid[y][x]))
			{
				process_player_found(game, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
	printf("Error: No player found in map\n");
	exit(1);
}
