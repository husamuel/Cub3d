/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:34:06 by diolivei          #+#    #+#             */
/*   Updated: 2025/06/04 17:38:41 by diolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../cub3d.h"

int	close_window(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

int	loop_hook_wrapper(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_game(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	else if (keycode == XK_Left)
		game->keys.left = 1;
	else if (keycode == XK_Right)
		game->keys.right = 1;
	else if (keycode == XK_w)
		game->keys.forward = 1;
	else if (keycode == XK_s)
		game->keys.backward = 1;
	else if (keycode == XK_a)
		game->keys.strafe_left = 1;
	else if (keycode == XK_d)
		game->keys.strafe_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_Left)
		game->keys.left = 0;
	else if (keycode == XK_Right)
		game->keys.right = 0;
	else if (keycode == XK_w)
		game->keys.forward = 0;
	else if (keycode == XK_s)
		game->keys.backward = 0;
	else if (keycode == XK_a)
		game->keys.strafe_left = 0;
	else if (keycode == XK_d)
		game->keys.strafe_right = 0;
	return (0);
}

void	update_game(t_game *game)
{
	int	updated;

	updated = 0;
	if (game->keys.left)
	{
		rotate_camera(game, 1);
		updated = 1;
	}
	if (game->keys.right)
	{
		rotate_camera(game, -1);
		updated = 1;
	}
	if (game->keys.forward || game->keys.backward
		|| game->keys.strafe_left || game->keys.strafe_right)
	{
		move_player(game);
		updated = 1;
	}
	if (updated)
	{
		draw_background(game);
		draw_walls(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	}
}
