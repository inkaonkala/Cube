/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:24:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/30 15:15:09 by iniska           ###   ########.fr       */
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
	
	if (game->map[game->player_y][game->player_x] == 'N')
		game->player_angl = 3 * PI / 2;
	else if (game->map[game->player_y][game->player_x] == 'E')
		game->player_angl = 0;
	else if (game->map[game->player_y][game->player_x] == 'S')
		game->player_angl = PI / 2;
	else if (game->map[game->player_y][game->player_x] == 'W')
		game->player_angl = PI;
	else
		printf("Player not found\n");
	
	game->fow = (FOW * PI / 180);
	game->mouse_on = false;
	game->rotation = 0;
	game->left_right = 0;
	game->up_down = 0;

	game->rays->int_x = (game->player_x * TILE) + TILE / 2;
	game->rays->int_y = (game->player_y * TILE) + TILE / 2;
}

float	distance(t_game *game, float x, float y)
{
	float	distance;

	distance = sqrt(pow(x - game->player_x, 2) + (pow(y - game->player_y, 2)));
	return (distance);
}