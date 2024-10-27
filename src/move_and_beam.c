/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_beam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:41:09 by iniska            #+#    #+#             */
/*   Updated: 2024/10/27 19:43:03 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
static void	rotate(t_game *game, int i)
{
	if (i == 1)
	{
		game->player_angl += ROTATIO_SPEED;
		if (game->player_angl > 2 * PI)
			game->player_angl -= 2 * PI;
	}
	else
	{
		game->player_angl -= ROTATIO_SPEED;
		if (game->player_angl < 0)
			game->player_angl += 2 * PI;
	}
}

static void	move_hook(t_game *game)
{
	if (game->rotation == 1)
		rotate(game, 1);
	if (game->rotation == -1)
		rotate(game, 0);
	// move_player(); ALL THE MOVEMENT SHOULD BE HERE!s
}	
*/

void	move_and_beam(void	*data)
{
	t_game *game;

	game = (t_game *) data;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
//	move_hook(game);
	raycast(game);
}