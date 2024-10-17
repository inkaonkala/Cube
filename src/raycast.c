/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:39:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/17 12:10:04 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


static float	get_horizon(t_game *game, float angl)
{
	float	x_step;
	float	y_step;
	float	x;
	float	y;
	int		ray_move;

	if (angl == 0)
		angl == 0.00001;
	y_step = TILE;
	x_step = TILE / tan(angl);

	y = floor(game->player_y / TILE) * TILE;
	ray_move = 
	
	printf("printer: %f", game->rays->ray_angl);
}

static float	get_wall_height(t_game *game, float angl)
{
	printf("printer: %f", game->rays->ray_angl);
}
*/

void raycast(t_game *game)
{
	double	horizon_line;
	double	verctical_line;
	int		ray;

	ray = 0;
	while (ray < WINDOW_WIDTH)
	{
	//	game->rays->ray_angl = update_rayangl();
		game->rays->wall_flag = false;
		horizon_line = get_horizon(game, game->rays->ray_angl);
		verctical_line = get_wall_height(game, game->ray->ray_angl);
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