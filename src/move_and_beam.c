/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_beam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:41:09 by iniska            #+#    #+#             */
/*   Updated: 2024/11/15 14:35:32 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	move_player(t_game *game, double move_x, double move_y)
{
	int		map_y;
	int		map_x;
	double	new_y;
	double	new_x;

	new_x = game->rays->p_x + move_x;
	new_y = game->rays->p_y + move_y;
	map_x = new_x / TILE;
	map_y = new_y / TILE;
	if (game->map[map_y][map_x] != '1' 
		&& game->map[map_y][game->rays->p_x / TILE] != '1' 
		&& game->map[game->rays->p_y / TILE][map_x] != '1')
	{
		game->rays->p_x = new_x;
		game->rays->p_y = new_y;
		if (game->rays->p_x % TILE == 0)
			game->rays->p_x += 1;
		if (game->rays->p_y % TILE == 0)
			game->rays->p_y += 1;
	}
	if (BONUS)
	{
		if (game->map[game->rays->p_x][game->rays->p_y] == 'G')
			game->death = true;
	}
}

static void	rotate(t_game *game, int i)
{
	if (i == 1)
	{
		game->player_angl += ROTATIO_SPEED;
		if (game->player_angl > 2 * PI)
			game->player_angl -= 2 * PI;
	}
	else
	{
		game->player_angl -= ROTATIO_SPEED;
		if (game->player_angl < 0)
			game->player_angl += 2 * PI;
	}
}

static void	wasd(t_game *game, double *move_x, double *move_y)
{
	if (game->left_right == -1) // D
	{
		*move_x = -sin(game->player_angl) * SPEED;
		*move_y = cos(game->player_angl) * SPEED;
		game->left_right = 0;
	}
	if (game->left_right == 1) // A
	{
		*move_x = sin(game->player_angl) * SPEED;
		*move_y = -cos(game->player_angl) * SPEED;
		game->left_right = 0;
	}
	if (game->up_down == -1) // S
	{
		*move_x = -cos(game->player_angl) * SPEED;
		*move_y = -sin(game->player_angl) * SPEED;
		game->up_down = 0;
 	}
	if (game->up_down == 1) // W
	{
		*move_x = cos(game->player_angl) * SPEED;
		*move_y = sin(game->player_angl) * SPEED;
		game->up_down = 0;
	}
}

static void	move_hook(t_game *game, double move_x, double move_y)
{
	wasd(game, &move_x, &move_y);

	if (game->rotation == 1)
		rotate(game, 1);
	if (game->rotation == -1)
		rotate(game, 0);

	game->up_down = 0;
	game->left_right = 0;
	game->rotation = 0;
	move_player(game, move_x, move_y);		
}	


void	move_and_beam(void	*data)
{
	t_game *game;

	game = (t_game *) data;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		printf("Bye bye!\n");
	}

	//if (BONUS)
	
	ghostie(game);
	keys(game);
	move_hook(game, 0, 0);
	game->mini_angle= game->player_angl;
	raycast(game);
	
	//bonus
	init_door(game);
	draw_mini_map(game);
	if (game->death == true)
	{
		ft_printf("DEATH!\n");
		game_over_image(game);
		//this segfaults cause no cleaning!
	}

}
