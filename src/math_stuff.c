/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:24:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/29 12:29:34 by iniska           ###   ########.fr       */
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
	printf("PLAYER X: %zu \n", game->player_x);
	printf("PLAYER Y: %zu \n", game->player_y);
	
	game->player_x = game->player_x * TILE + TILE / 2;
	game->player_y = game->player_y * TILE + TILE / 2;
	game->fow = (FOW * PI / 180);
	game->player_angl = PI;

//	game->player_angl =  atan2(game->player_y, game->player_x);
//	if (game->player_angl < 0)
//		game->player_angl += 2 * PI; // this needs to be counted according to player y and x, divided by PI, BUT EAST is 0 so let's use it
	
	// FOR TESTING ENDS
	
	game->mouse_on = false;
	game->rotation = 0;
	game->left_right = 0;
	game->up_down = 0;
}

float	distance(t_game *game, float x, float y)
{
	float	distance;

	distance = sqrt(pow(x - game->player_x, 2) + (pow(y - game->player_y, 2)));
	return (distance);
}