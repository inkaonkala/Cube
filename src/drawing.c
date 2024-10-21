/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:16:18 by iniska            #+#    #+#             */
/*   Updated: 2024/10/21 12:03:57 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_pixels(t_game *game, int x, int y, int colour)
{
	if (x < 0)
		return ;
	else if (x >= WINDOW_WIDTH)
		return ;
	if (y < 0)
		return ;
	if (y >= WINDOW_HEIGHT)
		return ;

	mlx_put_pixel(game->canvas, x, y, colour);
}