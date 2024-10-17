/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_beam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:41:09 by iniska            #+#    #+#             */
/*   Updated: 2024/10/17 10:31:01 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	move_and_beam(void	*data)
{
	t_game *game;

	game = (t_game *) data;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	//move_hook(game);
	raycast(game);
}