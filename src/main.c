/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/28 12:31:25 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main (int argc, char *argv[])
{
	//printf("%d", argc);
	//printf("%s", argv[0]);
	//printf("this is here for compile %s", argv[0]); 
	
	if (argc != 2)
		err_message_exit("Invalid input.");
	
	if (check_file_extesion(argv[1]) == 0)
		err_message_exit( "please provide a '.cub' file");
	
	t_game *game;

	game = calloc(1, sizeof(t_game));
	if(!game)
		err_message_exit("Malloc failed");
	
	//parse map
	init_game(game, argv[1]);


	t_minimap *mini;
	mini = ft_calloc(1, sizeof(t_minimap));
	if(!mini)
		err_message_exit("Malloc failed");
	//mini->mlx = mlx_init(800, 600, "Mini map", false);
    //if (!mini->mlx)
    //    return (1);
	//if (minimap(game, mini) == 1)
		//err_message_exit("minimap failed");
	//initializing the MLX library
	//Window Creation

	//need to free the game pointer	
	
	//initializing the MLX library
	game->rays = malloc(sizeof(t_rays));
	if(!game->rays)
		err_message_exit("Failed to malloc for the BEAM\n");

	count_values(game);
	screenpop(game); // opens a window 
	free(game);
	// 清理並結束
    mlx_delete_image(mini->mlx, mini->background);
    mlx_terminate(mini->mlx);
	return (0);
}
