/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:06:33 by iniska            #+#    #+#             */
/*   Updated: 2024/10/31 10:25:11 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


static void	floor_n_ceiling(t_game *game, int ray, double bot_pxl, double top_pxl)
{
	double	i;

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

	wall_hi = 0;

//	printf("player: %f, ray: %f\n", game->player_angl, game->rays->ray_angl);

	if (fabs(game->rays->distance) < 0.0001)
		game->rays->distance = 0.0001;

	game->rays->distance *= cos((game->player_angl - game->rays->ray_angl));

	if (fabs(game->rays->distance) < 0.0001)
		game->rays->distance = 0.0001;

	wall_hi = fabs((TILE / game->rays->distance) * (WINDOW_WIDTH / 2) / tan(game->fow));

	bot_pixl = (WINDOW_HEIGHT / 2) + (wall_hi / 2);
	top_pixl = (WINDOW_HEIGHT / 2) - (wall_hi / 2);

	if (bot_pixl > WINDOW_HEIGHT)
		bot_pixl = WINDOW_HEIGHT;
	if (top_pixl < 0)
		top_pixl = 0;
	game->rays->i = ray;

	draw_wall(game, ray, bot_pixl, top_pixl);
	
	floor_n_ceiling(game, ray, bot_pixl, top_pixl);

}