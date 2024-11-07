/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:24:06 by iniska            #+#    #+#             */
/*   Updated: 2024/11/04 14:58:27 by yhsu             ###   ########.fr       */
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

void	save_images_to_struct(t_game *game)
{
	game->no_texture = mlx_load_png(game->no_texture_path);
	colour_flip((uint32_t *)game->no_texture->pixels, game->no_texture->width, game->no_texture->height);
	game->so_texture = mlx_load_png(game->so_texture_path);
	colour_flip((uint32_t *)game->so_texture->pixels, game->so_texture->width, game->so_texture->height);
	game->we_texture = mlx_load_png(game->we_texture_path);
	colour_flip((uint32_t *)game->we_texture->pixels, game->we_texture->width, game->we_texture->height);
	game->ea_texture = mlx_load_png(game->ea_texture_path);
	colour_flip((uint32_t *)game->ea_texture->pixels, game->ea_texture->width, game->ea_texture->height);
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
	game->width = game->longest;

	game->rays->p_x = (game->player_x * TILE) + TILE / 2;
	game->rays->p_y = (game->player_y * TILE) + TILE / 2;

	save_images_to_struct(game);
}

float	distance(t_game *game, float x, float y)
{
	float	distance;
	float	new_x;
	float	new_y;

	new_x = x - game->rays->p_x;
	new_y = y - game->rays->p_y;

	distance = sqrt(pow(new_x, 2) + (pow(new_y, 2)));
	return (distance);
}