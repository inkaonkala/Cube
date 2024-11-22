/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:39:06 by iniska            #+#    #+#             */
/*   Updated: 2024/11/22 09:23:00 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static float	get_horizon(t_game *game, float angl, bool *ghosty)
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
	y = floor(game->rays->p_y / TILE) * TILE;
	ray_move = move_ray(angl, &y, &y_step, 0);
	x = game->rays->p_x + (y - game->rays->p_y) / tan(angl);
	if (angl > PI / 2 && angl < 3 * PI / 2)
		x_step = -fabs(x_step);
	else
		x_step = fabs(x_step);
	while (!wall(game, x, y - ray_move, ghosty))
	{
		x += x_step;
		y += y_step;
	}
	game->rays->horizon_inter_x = x;
	game->rays->horizon_inter_y = y;
	return (distance(game, x, y));
}

static float	get_wall_height(t_game *game, float angl, bool *ghosty)
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
	x = floor(game->rays->p_x / TILE) * TILE;
	ray_move = move_ray(angl, &x, &x_step, 1);
	y = game->rays->p_y + (x - game->rays->p_x) * tan(angl);
	if (angl > 0 && angl < PI)
		y_step = fabs(y_step);
	else
		y_step = -fabs(y_step);
	while (!wall(game, x - ray_move, y, ghosty))
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
	angl = fmod(angl, 2 * PI);
	if (angl < 0)
		angl += 2 * PI;
	return (angl);
}

static void	it_is_a_wall(t_game *game, double horizon_line)
{
	game->rays->distance = horizon_line;
	game->rays->wall_flag = true;
}

void	raycast(t_game *game)
{
	double	horizon_line;
	double	vertical_line;
	bool	ghosty;
	int		ray;

	ray = 0;
	game->rays->ray_angl = game->player_angl - (game->fow / 2);
	while (ray < WIN_WIDTH)
	{
		ghosty = false;
		game->rays->ray_angl = update_rayangl(game->rays->ray_angl);
		game->rays->wall_flag = false;
		horizon_line = get_horizon(game, game->rays->ray_angl, &ghosty);
		vertical_line = get_wall_height(game, game->rays->ray_angl, &ghosty);
		if (vertical_line <= horizon_line)
			game->rays->distance = vertical_line;
		else
			it_is_a_wall(game, horizon_line);
		set_walls(game, ray);
		if (ghosty)
			update_g(game);
		game->rays->ray_angl += (game->fow / WIN_WIDTH);
		ray++;
	}
}
