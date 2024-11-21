/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:41:32 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/21 15:54:09 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	find_direction(t_game *game)
{
	if (game->mini_angle > 4.3186 && game->mini_angle <= 5.1038)
		return (0);
	else if (game->mini_angle > 5.1038 && game->mini_angle <= 6.3)
		return (1);
	else if (game->mini_angle > 5.889 || game->mini_angle <= 0.3926)
		return (2);
	else if (game->mini_angle > 0.3926 && game->mini_angle <= 1.1778)
		return (3);
	else if (game->mini_angle > 1.1778 && game->mini_angle <= 1.963)
		return (4);
	else if (game->mini_angle > 1.963 && game->mini_angle <= 2.7482)
		return (5);
	else if (game->mini_angle > 2.7482 && game->mini_angle <= 3.5334)
		return (6);
	else if (game->mini_angle > 3.5334 && game->mini_angle <= 4.3186)
		return (7);
	return (-1);
}

static void	find_texture( t_game *game, float direction)
{
	game->miniplayer_text = NULL;
	if (direction == 0)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_0.png");
	else if (direction == 1)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_1.png");
	else if (direction == 2)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_2.png");
	else if (direction == 3)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_3.png");
	else if (direction == 4)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_4.png");
	else if (direction == 5)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_5.png");
	else if (direction == 6)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_6.png");
	else if (direction == 7)
		game->miniplayer_text = mlx_load_png("./textures/minimap_player_7.png");
	game->mini_player = mlx_texture_to_image(game->mlx, game->miniplayer_text);
	if (!game->mini_player)
	{
		mlx_strerror(mlx_errno);
		clean_all_exit(game, "mlx_errno");
	}
	mlx_delete_texture(game->miniplayer_text);
}

void	draw_player(t_game *game)
{
	long	height;
	float	direction;

	direction = find_direction(game);
	find_texture(game, direction);
	height = MINIMAP_SIDE / 2;
	mlx_image_to_window(game->mlx, game->mini_player,
		(MINIMAP_SIDE / 2) - 8, height - 8);
	game->mini_player->instances[0].z = 1;
}
