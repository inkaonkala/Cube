/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:06:33 by iniska            #+#    #+#             */
/*   Updated: 2024/10/18 13:24:50 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	floor_n_ceiling(t_game *game, int ray, double bot_pxl, double top_pxl)
{
	int	i;

	i = bot_pxl;
	while (i < WINDOW_HEIGHT)
		set_pixels(game, ray, i++, 0xd6ebff); //floor
	i = 0;
	while (i  < top_pxl)
		set_pixels(game, ray, i++, 0x2694ab); // ceiling
}

void	set_walls(t_game *game, int ray)
{
	double	wall_hi;
	double	top_pixl;
	double	bot_pixl;

	game->rays->distance *= cos(beam_angl(game->rays->ray_angl - game->player_angl));
	
	wall_hi = abs(TILE / game->rays->distance) * (WINDOW_WIDTH / 2) / tan(game->player_angl);

	bot_pixl = (WINDOW_HEIGHT / 2) + (wall_hi / 2);
	top_pixl = (WINDOW_HEIGHT / 2) - (wall_hi / 2);

	if (bot_pixl > WINDOW_HEIGHT)
		bot_pixl = WINDOW_HEIGHT;
	if (top_pixl < 0)
		top_pixl = 0;
	game->rays->i = ray;

	floor_n_ceiling(game, ray, bot_pixl, top_pixl);
	//draw_wall(game, ray, bot_pixl, top_pixl);

}