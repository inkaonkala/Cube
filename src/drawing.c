/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:16:18 by iniska            #+#    #+#             */
/*   Updated: 2024/10/25 13:44:17 by iniska           ###   ########.fr       */
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

void	draw_wall(t_game *game, int ray, double bot_pixl, double top_pixl)
{
	int	color;

	color = 0xf6a192;

	while (top_pixl < bot_pixl)
		set_pixels(game, ray, top_pixl++, color);

}