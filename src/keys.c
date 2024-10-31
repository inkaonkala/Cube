/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:54:19 by iniska            #+#    #+#             */
/*   Updated: 2024/10/28 11:36:47 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	release_key(mlx_key_data_t key_data, t_game *game)
{
	if (key_data.key == MLX_KEY_LEFT && key_data.key == MLX_RELEASE)
		game->rotation = 0;
	if (key_data.key == MLX_KEY_RIGHT && key_data.key == MLX_RELEASE)
		game->rotation = 0;
}

void	keys(mlx_key_data_t key_data, void *data)
{
	t_game *game;

	game = data;
	if (key_data.key == MLX_KEY_LEFT && key_data.action == MLX_PRESS)
		game->rotation = -1;
	else if (key_data.key == MLX_KEY_RIGHT && key_data.action == MLX_PRESS)
		game->rotation = -1;
	release_key(key_data, game);
}

void	mouse_move(double x, double y, void *data)
{
	t_game *game;

	game = data;

	if (!game->mouse_on)
		return ;
		
	double center_x = WINDOW_WIDTH / 2.0;
    double sensitivity = 0.003; // Adjust for desired rotation speed

    // Calculate rotation based on horizontal mouse movement
	printf("%f", y);
    game->player_angl += (x - center_x) * sensitivity;

    // Clamp the angle between 0 and 2 * PI
    if (game->player_angl > 2 * PI)
        game->player_angl -= 2 * PI;
    else if (game->player_angl < 0)
        game->player_angl += 2 * PI;

    // Optional: Reset mouse position to center
    mlx_set_mouse_pos(game->mlx, center_x, WINDOW_HEIGHT / 2.0);
}

void mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void *data)
{
    t_game *game = (t_game *)data;

    if (button == MLX_MOUSE_BUTTON_LEFT)
    {
        if (action == MLX_PRESS)
            game->mouse_on = true;
        else if (action == MLX_RELEASE)
            game->mouse_on = false;
    }
	printf("%u", mods);
}