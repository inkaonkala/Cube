/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 08:07:33 by iniska            #+#    #+#             */
/*   Updated: 2024/11/21 14:22:37 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	check_door_position(t_game *game, char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				count++;
				game->door_x = j;
				game->door_y = i;
			}
			j++;
		}
		i++;
	}
	if (count > 1)
		clean_all_exit(game, "only ONE door is allowed.");
}

static void	init_door_texture(t_game *game)
{
	if (game->door_open_texture)
		mlx_delete_texture(game->door_open_texture);
	game->door_open_texture = mlx_load_png(DOOR_PATH_OPEN);
	if (game->door_open_texture)
		colour_flip((uint32_t *)game->door_open_texture->pixels,
			game->door_open_texture->width, game->door_open_texture->height);
	if (!game->door_open_texture)
	{
		mlx_strerror(mlx_errno);
		clean_all_exit(game, "mlx_png_err");
	}
	if (game->door_close_texture)
		mlx_delete_texture(game->door_close_texture);
	game->door_close_texture = mlx_load_png(DOOR_PATH_CLOSE);
	if (game->door_close_texture)
		colour_flip((uint32_t *)game->door_close_texture->pixels,
			game->door_close_texture->width, game->door_close_texture->height);
	if (!game->door_close_texture)
	{
		mlx_strerror(mlx_errno);
		clean_all_exit(game, "mlx_png_err");
	}
}

void	init_door(t_game *game)
{
	if (game->door_state != true)
		game->door_state = false;
	game->hit_door = false;
	game->d = '\0';
	check_door_position(game, game->map);
	init_door_texture(game);
}

void	check_door(t_game *game)
{
	float	distance;
	int		dx;
	int		dy;

	dx = (game->rays->p_x / TILE) - game->door_x;
	dy = (game->rays->p_y / TILE) - game->door_y;
	distance = sqrt((dx * dx) + (dy * dy));
	if (distance < 1.3 && game->d == 'D')
	{
		if (game->door_state == false)
		{
			game->door_state = true;
		}
	}
	else if (distance > 1.5)
		game->door_state = false;
}
