/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:58:42 by iniska            #+#    #+#             */
/*   Updated: 2024/11/25 09:10:13 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	death_checker(t_game *game, double radius)
{
	double	c_x;
	double	c_y;
	double	player_x;
	double	player_y;
	double	distance;

	radius = TILE * 1.2;
	c_x = game->g->g_x * TILE + TILE / 2;
	c_y = game->g->g_y * TILE + TILE / 2;
	player_x = game->rays->p_x;
	player_y = game->rays->p_y;
	distance = sqrt(pow(player_x - c_x, 2) + pow(player_y - c_y, 2));
	if (distance <= radius)
		game->death = true;
}

bool	valid(t_game *game, int y, int x, int i)
{
	if (i == 1)
	{
		if ((game->map[y][x] != '1' && game->map[y][game->rays->p_x / TILE]
		!= '1' && game->map[game->rays->p_y / TILE][x] != '1' )
		|| (game->map[y][x] != 'G' && game->map[y][game->rays->p_x / TILE]
		!= 'G' && game->map[game->rays->p_y / TILE][x] != 'G'))
			return (true);
	}
	else if (i == 2)
	{
		if (game->map[y][x] != '1'
		&& game->map[y][game->rays->p_x / TILE] != '1'
		&& game->map[game->rays->p_y / TILE][x] != '1'
		&& game->map[y][x] != '1' && game->map[y][game->rays->p_x / TILE] != 'D'
		&& game->map[game->rays->p_y / TILE][x] != 'D')
			return (true);
	}
	return (false);
}
