#include "./cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error: Failed to initialize mlx\n");
		return (1);
	}
	game->win = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "cub3D");
	if (!game->win)
	{
		printf("Error: Failed to create window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (1);
	}
	return (0);
}

static int	init_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	if (!game->img)
	{
		printf("Error: Failed to create image\n");
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (1);
	}
	return (0);
}

static void	render_scene(t_game *game)
{
	draw_background(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask,
		close_window, game);
	mlx_loop_hook(game->mlx, loop_hook_wrapper, game);
}

int	init_window(t_game *game)
{
	if (init_mlx(game))
		return (1);
	if (init_image(game))
		return (1);
	render_scene(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
