/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:24:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/17 14:03:21 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// count the game->player_angl, game->rays->ray_angl, game->fow
void	count_values(t_game *game)
{
	game->player_angl = 0; // this needs to be counted according to player y and x, divided by PI, BUT EAST is 0 so let's use it
	game->fow = (FOW * PI / 180);
	game->rays->ray_angl = game->player_angl - (game->fow / 2);
	printf("%f", game->rays->n_ray);
}

float	distance(t_game *game, float x, float y)
{
	
}