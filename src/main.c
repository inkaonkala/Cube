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
		err_message_exit("Malloc fail");
	
	//parse map
	init_game(game, argv[1]);
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

	return (0);
}
