/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:04:39 by iniska            #+#    #+#             */
/*   Updated: 2024/10/17 10:22:45 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	screenpop(t_game *game)
{
	
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "This is a cube", true);
	if(!game->mlx)
		err_message_exit("Mlx failed to create a window\n Or, was it me ....\n");
	
	game->canvas = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if(!game->canvas)
		err_message_exit("No canvas for screen\n");
	
	mlx_image_to_window(game->mlx, game->canvas, 0, 0);
	mlx_loop_hook(game->mlx, move_and_beam, game); // mave_and_beam() has the movehook and raycast in it!
	mlx_loop(game->mlx);
}