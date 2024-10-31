/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:16:18 by iniska            #+#    #+#             */
/*   Updated: 2024/10/31 11:11:21 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_pixels(t_game *game, double x, double y, int colour)
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

/*
static void	get_pics_for_wall(t_game *game)
{
	if (game->rays->wall_flag)
	{
		if (game->rays->ray_angl > 0 && game->rays->ray_angl < PI)
			return (game->so_texture);
		else
			return (game->no_texture);
	}
	else
	{
		if (game->rays->ray_angl > PI / 2 && game->rays->ray_angl < 3 * PI / 2)
			return (game->we_texture);
		else
			return (game->ea_texture);
	}
}

void	draw_wall(t_game *game, double bot_pixl, double top_pixl, double wall_hi)
*/

void	draw_wall(t_game *game, int ray, double bot_pixl, double top_pixl)
{
	// to test
	int	color;

	color = 0xf6a192;

	while (top_pixl < bot_pixl)
		set_pixels(game, ray, top_pixl++, color);

	/*
	mlx_texture_t	*pic;
	uint32_t		*pixels;
	double			x;
	double			y;
	int				pos;

	pic = get_pics_for_wall(game);
	//check it works?)
	// return ;
	pixels = (uint32_t *)texture->pixels;
	x = get_offset()
	y = (top_pixl - (WINDOW_HEIGHT / 2) + (wall_hi / 2)) * (double)texture->heigt / wall_hi;
	if (y < 0)
		y = 0;
	while (top_pixl < bot_pixl)
	{
		pos = (int)y * texture->width + (int)x;
		if (pos = 0)
			return ;
		set_pixels(game->canvas, game->index, top_pixl, color);
		pic += (double)texture->height / wall_hi;
		top_pixl++;
	}
	*/
	

}