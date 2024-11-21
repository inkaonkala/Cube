/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:13:20 by iniska            #+#    #+#             */
/*   Updated: 2024/11/19 11:17:28 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_pixels(t_game *game, double x, double y, int colour)
{
	if (x < 0)
		return ;
	else if (x >= WIN_WIDTH)
		return ;
	if (y < 0)
		return ;
	if (y >= WIN_HEI)
		return ;
	mlx_put_pixel(game->canvas, x, y, colour);
}

double	get_setof_x(t_game *game, mlx_texture_t *pic)
{
	double	x;

	x = 0;
	if (!game || !game->rays || !pic || pic->width == 0)
	{
		printf("No Picture\n");
		return (x);
	}
	if (game->rays->wall_flag == true)
		x = (int)fmodf((game->rays->horizon_inter_x
					* (pic->width / TILE)), pic->width);
	else
		x = (int)fmodf((game->rays->vertical_inter_y
					* (pic->width / TILE)), pic->width);
	return (x);
}
