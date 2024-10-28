/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/28 11:03:12 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main (int argc, char *argv[])
{
	//printf("%d", argc);
	//printf("%s", argv[0]);
	//printf("this is here for compile %s", argv[0]); 
	
	if (argc != 2 && argv)
		err_message_exit("Invalid input.");
	//	SEGFAULT!
	if (check_file_extesion(argv[1]) == 0)
		err_message_exit("please provide a '.cub' file");

	printf("HELLO!\n");
	t_game *game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if(!game)
		err_message_exit("Malloc fail");
	

	//parse map
	init_game(game, argv[1]);
	
	//initializing the MLX library
	game->rays = malloc(sizeof(t_rays));
	if(!game->rays)
		err_message_exit("Failed to malloc for the BEAM\n");
	count_values(game);
	screenpop(game); // opens a window 
	free(game);

	return (0);
}
