/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:04:39 by iniska            #+#    #+#             */
/*   Updated: 2024/10/27 20:43:49 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
static void test_canvas(void	*data)
{
	t_game *game;

	game = (t_game *) data;
    for (int x = 10; x < 60; x++)
    {
        for (int y = 10; y < 60; y++)
        {
           printf("POTATOES\n");
		   mlx_put_pixel(game->canvas, x, y,  0xd6ebff);
        }
    }
}
*/

/*
// MOVE THIS TO KEYS.c !

static void	release_key(mlx_key_data_t key_data, t_game *game)
{
	if (key_data.key == MLX_KEY_LEFT && key_data.key == MLX_RELEASE)
		game->rotation = 0;
	if (key_data.key == MLX_KEY_RIGHT && key_data.key == MLX_RELEASE)
		game->rotation = 0;
}

static void	keys(mlx_key_data_t key_data, void *data)
{
	t_game *game;

	game = data;
	if (key_data.key == MLX_KEY_LEFT && key_data.action == MLX_PRESS)
		game->rotation = -1;
	else if (key_data.key == MLX_KEY_RIGHT && key_data.action == MLX_PRESS)
		game->rotation = -1;
	release_key(key_data, game);
}
	

/// UNTILL HERE
*/

void	screenpop(t_game *game)
{
	if(!(game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "This is a cube", true)))
		err_message_exit("Mlx failed to create a window\n Or, was it me ....\n");
	
	if(!(game->canvas = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
		err_message_exit("No canvas for screen\n");
	
	if(mlx_image_to_window(game->mlx, game->canvas, 0, 0) == -1)
		err_message_exit("Canvas not working\n");
	
	
//	mlx_loop_hook(game->mlx, test_canvas, game);


	mlx_loop_hook(game->mlx, move_and_beam, game);
//	mlx_key_hook(game->mlx, &keys, &game->mlx); //void mlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param);
	
	mlx_loop(game->mlx);
//	mlx_terminate(game->mlx);
}