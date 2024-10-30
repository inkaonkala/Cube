/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:39:06 by iniska            #+#    #+#             */
/*   Updated: 2024/10/30 15:23:02 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	wall(t_game *game, float x, float y)
{
    size_t map_x;
    size_t map_y;

    if (x < 0 || y < 0)
        return (1);
    map_x = floor(x / TILE);
    map_y = floor(y / TILE);
	if (game->height <= map_y || game->width <= map_x)
		return (1);
	if (game->map[map_y] && map_x < ft_strlen(game->map[map_y])) // check this
	{
		if (game->map[map_y][map_x] == '1')
			return (1);
	}
    return (0);
}

static int		move_ray(float angl, float *inter, float *step, int is_vert)
{
	if (!is_vert)
	{
		if(angl > 0 && angl < PI)
		{
			*inter += TILE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angl >= PI / 2 && angl <= 3 * PI / 2))
		{
			*inter += TILE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

static float	get_horizon(t_game *game, float angl)
{
	float	x_step;
	float	y_step;
	float	x;
	float	y;
	int		ray_move;

	if (angl == 0)
		angl = 0.00001;
	
	y_step = TILE;
	x_step = TILE / tan(angl);

	y = floor(game->rays->int_y / TILE) * TILE;
	ray_move = move_ray(angl, &y, &y_step, 0);
	x = game->rays->int_x + (y - game->rays->int_y) / tan(angl);

	if (angl > PI / 2 && angl < 3 * PI / 2)
		x_step = -fabs(x_step);
	else
		x_step = fabs(x_step);
	
	while (!wall(game, x, y - ray_move))
	{
		x += x_step;
		y += y_step;
	}
	game->rays->horizon_inter_x = x;
	game->rays->horizon_inter_y = y;
	return (distance(game, x, y));
}

static float	get_wall_height(t_game *game, float angl)
{
	float	x_step;
	float	y_step;
	float	x;
	float	y;
	int		ray_move;

	if (angl == 0)
		angl = 0.00001;

	y_step = TILE * tan(angl);
	x_step = TILE;


	x = floor(game->rays->int_x / TILE) * TILE;
	ray_move = move_ray(angl, &x, &x_step, 1);
	y = game->rays->int_y + (x - game->rays->int_x) * tan(angl);
	if (angl > 0 && angl < PI)
		y_step = fabs(y_step);
	else
		y_step = -fabs(y_step);
	while (!wall(game, x - ray_move, y))
	{
		x += x_step;
		y += y_step;
	}
	game->rays->vertical_inter_x = x;
	game->rays->vertical_inter_y = y;
	return (distance(game, x, y));
}


static float	update_rayangl(float angl)
{
	if (angl <= 0)
	{
		angl += 2 * PI;
		return (angl);
	}
	if (angl > 2 * PI)
	{
		angl -= 2 * PI;
		return (angl);
	}
	return (angl);
}

void raycast(t_game *game)
{
	double	horizon_line;
	double	vertical_line;
	int		ray;

	ray = 0;
	while (ray < WINDOW_WIDTH)
	{
		game->rays->ray_angl = update_rayangl(game->rays->ray_angl);
		game->rays->wall_flag = false;
		horizon_line = get_horizon(game, game->rays->ray_angl);
		vertical_line = get_wall_height(game, game->rays->ray_angl);
		if(vertical_line <= horizon_line)
			game->rays->distance = vertical_line;
		else
		{
			game->rays->distance = horizon_line;
			game->rays->ray_angl = true;
		}
		set_walls(game, ray);
		ray++;
		game->rays->ray_angl += (game->fow / WINDOW_WIDTH);
	}

}