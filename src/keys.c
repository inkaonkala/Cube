/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:54:19 by iniska            #+#    #+#             */
/*   Updated: 2024/10/29 13:06:00 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	keys(t_game *game)
{
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->up_down = 1;
    else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->up_down = -1;
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->left_right = 1;
    else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->left_right = -1;
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->rotation = -1;
    else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation = 1;
	
}

void	mouse_move(double x, double y, void *data)
{
	t_game	*game;

	game = data;
	if (!game->mouse_on)
		return ;		
	double center_x = WINDOW_WIDTH / 2.0;
    double sensitivity = ROTATIO_SPEED; // Adjust for desired rotation speed
	y = 0;	
    game->player_angl += (x - center_x) * sensitivity;
    if (game->player_angl > 2 * PI)
		game->player_angl -= 2 * PI;
    else if (game->player_angl < 0)
		game->player_angl += 2 * PI;

	mlx_set_mouse_pos(game->mlx, center_x, WINDOW_HEIGHT / 2.0);
}

void mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void *data)
{
	t_game *game = (t_game *)data;

	if	(button == MLX_MOUSE_BUTTON_LEFT)
    {
        if (action == MLX_PRESS)
			game->mouse_on = true;
		else if (action == MLX_RELEASE)
			game->mouse_on = false;
    }
	printf("%u", mods);
}