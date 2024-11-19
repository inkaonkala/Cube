/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:15:32 by iniska            #+#    #+#             */
/*   Updated: 2024/11/19 12:28:55 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	wall(t_game *game, float x, float y, bool *ghosty)
{
	size_t	map_x;
	size_t	map_y;

	if (x < 0 || y < 0)
		return (1);
	map_x = floor(x / TILE);
	map_y = floor(y / TILE);
	if (game->height <= map_y || game->longest <= map_x)
		return (1);
	if (game->map[map_y] && map_x <= ft_strlen(game->map[map_y]))
	{
		if (game->map[map_y][map_x] == 'G')
			*ghosty = true;
		if (game->map[map_y][map_x] == 'D')
		{
			game->hit_door = true;
			ghosty = false;
			return (2);
		}
		else if (game->map[map_y][map_x] == '1')
			return (1);
	}
	ghosty = false;
	return (0);
}

int	move_ray(float angl, float *inter, float *step, int is_vert)
{
	if (!is_vert)
	{
		if (angl > 0 && angl < PI)
		{
			*inter += TILE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angl > PI / 2 && angl < 3 * PI / 2))
		{
			*inter += TILE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}
