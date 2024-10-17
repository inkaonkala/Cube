/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:39:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/17 09:23:22 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
static float	get_horizon(t_game *game)
{
	printf("printer: %f", game->rays->ray_angl);
}

static float	get_wall_height(t_game *game)
{
	printf("printer: %f", game->rays->ray_angl);
}
*/

void raycast(t_game *game)
{
	//double	horizon_line;
	//double	verctical_line;
	int		ray;

	ray = 0;
	/*
	game->rays->ray_angl = game->player_angl - (game->fow / 2);
	while (ray < WINDOW_WIDTH)
	{
		game->rays->wall_flag = false;
		horizon_line = get_horizon();
		verctical_line = get_wall_height();
		if(verctical_line <= horizon_line)
			game->rays->distance = verctical_line;
		else
		{
			game->rays->distance = horizon_line;
			game->rays->ray_angl = true;
		}
		set_walls(game, ray);
		ray++;
		game->rays->ray_angl += (game->fow / WINDOW_WIDTH);

	}
	*/
	printf("printer: %d", ray);
	printf("printer: %f", game->rays->ray_angl);

}