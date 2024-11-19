/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:54:19 by iniska            #+#    #+#             */
/*   Updated: 2024/11/19 11:03:34 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	wasd(t_game *game, double *move_x, double *move_y)
{
	if (game->left_right == -1)
	{
		*move_x = -sin(game->player_angl) * SPEED;
		*move_y = cos(game->player_angl) * SPEED;
		game->left_right = 0;
	}
	if (game->left_right == 1)
	{
		*move_x = sin(game->player_angl) * SPEED;
		*move_y = -cos(game->player_angl) * SPEED;
		game->left_right = 0;
	}
	if (game->up_down == -1)
	{
		*move_x = -cos(game->player_angl) * SPEED;
		*move_y = -sin(game->player_angl) * SPEED;
		game->up_down = 0;
	}
	if (game->up_down == 1)
	{
		*move_x = cos(game->player_angl) * SPEED;
		*move_y = sin(game->player_angl) * SPEED;
		game->up_down = 0;
	}
}

static void	keys_two(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->left_right = 1;
		game->s = 'W';
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->left_right = -1;
		game->s = 'E';
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_E))
	{
		game->d = 'D';
		game->win = true;
	}
}

void	keys(t_game *game)
{	
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->up_down = 1;
		game->s = 'N';
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->up_down = -1;
		game->s = 'S';
	}
	keys_two(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->rotation = -1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation = 1;
}

void	mouse_move(double x, double y, void *data)
{
	t_game	*game;
	double	center_x;
	double	sensitivity;

	game = data;
	if (!game->mouse_on)
		return ;
	center_x = WIN_WIDTH / 2.0;
	sensitivity = ROTATIO_SPEED / 2;
	game->player_angl += (x - center_x) * sensitivity;
	if (game->player_angl > 2 * PI)
		game->player_angl -= 2 * PI;
	else if (game->player_angl < 0)
		game->player_angl += 2 * PI;
	mlx_set_mouse_pos(game->mlx, center_x, WIN_HEI / 2.0);
	if (y > 100000)
		ft_printf("This is here just to compile\n");
}

void	mouse_press(mouse_key_t but, action_t ac, modifier_key_t m, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	if (but == MLX_MOUSE_BUTTON_LEFT)
	{
		if (ac == MLX_PRESS)
			game->mouse_on = true;
		else if (ac == MLX_RELEASE)
			game->mouse_on = false;
	}
	if (m > 1000000)
		ft_printf("This is here for compile\n");
}
