/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:06:33 by iniska            #+#    #+#             */
/*   Updated: 2024/11/19 10:13:38 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static uint32_t	hexax(uint32_t r, uint32_t g, uint32_t b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

static void	floor_n_ceil(t_game *game, int ray, double bot_pxl, double top_pxl)
{
	double		i;
	uint32_t	floor;
	uint32_t	ceil;

	floor = hexax(game->floor_r, game->floor_g, game->floor_b);
	ceil = hexax(game->ceiling_r, game->ceiling_g, game->ceiling_b);
	i = bot_pxl;
	while (i < WIN_HEI)
		set_pixels(game, ray, i++, floor);
	i = 0;
	while (i < top_pxl)
		set_pixels(game, ray, i++, ceil);
}

void	set_walls(t_game *game, int ray)
{
	double	wall_hi;
	double	top_pixl;
	double	bot_pixl;

	wall_hi = 0;
	game->rays->distance *= cos((game->player_angl - game->rays->ray_angl));
	if (fabs(game->rays->distance) < 0.0001)
		game->rays->distance = 0.0001;
	wall_hi = fabs((TILE / game->rays->distance)
			* (WIN_WIDTH / 2) / tan(game->fow));
	bot_pixl = (WIN_HEI / 2) + (wall_hi / 2);
	top_pixl = (WIN_HEI / 2) - (wall_hi / 2);
	if (bot_pixl > WIN_HEI)
		bot_pixl = WIN_HEI;
	if (top_pixl < 0)
		top_pixl = 0;
	game->rays->i = ray;
	draw_wall(game, bot_pixl, top_pixl, wall_hi);
	floor_n_ceil(game, ray, bot_pixl, top_pixl);
}
