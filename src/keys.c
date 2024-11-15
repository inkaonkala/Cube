/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:54:19 by iniska            #+#    #+#             */
/*   Updated: 2024/11/15 14:35:02 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	keys(t_game *game)
{	
    if (mlx_is_key_down(game->mlx, MLX_KEY_W) )
	{
		game->up_down = 1;
		game->s = 'N';
	}
    else if ( mlx_is_key_down(game->mlx, MLX_KEY_S) )
	{
		game->up_down = -1;
		game->s = 'S';
	}
    if ( mlx_is_key_down(game->mlx, MLX_KEY_A) )
	{
		game->left_right = 1;
		game->s = 'W';
	}
    else if ( mlx_is_key_down(game->mlx, MLX_KEY_D) )
	{
		game->left_right = -1;
		game->s = 'E';
	}
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
    double sensitivity = ROTATIO_SPEED / 2; // Adjust for desired rotation speed
    game->player_angl += (x - center_x) * sensitivity;
    if (game->player_angl > 2 * PI)
		game->player_angl -= 2 * PI;
    else if (game->player_angl < 0)
		game->player_angl += 2 * PI;
	mlx_set_mouse_pos(game->mlx, center_x, WINDOW_HEIGHT / 2.0);
	if (y > 100000)
		ft_printf("This is here just to compile\n");
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
	if (mods > 1000000)
		ft_printf("This is here for compile\n");
}