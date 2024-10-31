/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:24:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/28 11:25:39 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	beam_angl(float angl)
{
	if (angl < 0)
		angl += (2 * PI);
	if (angl > (2 * PI))
		angl -= (2 * PI);
	return (angl);
}

// count the game->player_angl, game->rays->ray_angl, game->fow
void	count_values(t_game *game)
{
	// FOR TESTING
	game->player_x = 20;
	game->player_y = 20;
	game->player_angl =  atan2(game->player_y, game->player_x);
	if (game->player_angl < 0)
		game->player_angl += 2 * PI; // this needs to be counted according to player y and x, divided by PI, BUT EAST is 0 so let's use it
	
	// FOR TESTING ENDS
	game->mouse_on = false;
	game->rotation = 0;
	game->fow = (FOW * PI / 180);
	game->rays->ray_angl = game->player_angl - (game->fow / 2);
}

float	distance(t_game *game, float x, float y)
{
	float	distance;

	distance = sqrt(pow(x - game->player_x, 2) + (pow(y - game->player_y, 2)));
	return (distance);
}