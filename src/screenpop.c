/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:04:39 by iniska            #+#    #+#             */
/*   Updated: 2024/11/19 10:11:51 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	screenpop(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEI, "Escape!", true);
	if (!game->mlx)
		err_message_exit("Mlx failed to create a window\n Or, was it me ....\n");
	game->canvas = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEI);
	if (!game->canvas)
		err_message_exit("No canvas for screen\n");
	if (mlx_image_to_window(game->mlx, game->canvas, 0, 0) == -1)
		err_message_exit("Canvas not working\n");
	mlx_loop_hook(game->mlx, move_and_beam, game);
	mlx_cursor_hook(game->mlx, mouse_move, game);
	mlx_mouse_hook(game->mlx, mouse_press, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
