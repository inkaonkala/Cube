/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_beam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:41:09 by iniska            #+#    #+#             */
/*   Updated: 2024/11/21 10:36:24 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	move_and_beam(void	*data)
{
	t_game	*game;

	game = (t_game *) data;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		printf("Bye bye!\n");
	}
	if (BONUS > 0)
		ghostie(game);
	keys(game);
	move_hook(game, 0, 0);
	game->mini_angle = game->player_angl;
	raycast(game);
	if (BONUS > 0)
	{
		init_door(game);
		draw_mini_map(game);
	}
	if (game->death == true)
		game_over_image(game);
	if (game->win == true)
		game_over_image(game);
}
