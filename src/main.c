/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/23 14:26:52 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main (int argc, char *argv[])
{
	printf("%d", argc);
	printf("this is here for compile %s", argv[0]); 
	
	t_game *game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if(!game)
		err_message_exit("Malloc fail");
	
	//if (argc != 2)
	//	err_message_exit(game, "Invalid input.");
	if (check_file_extesion(argv[1]))
		err_message("please provide a .cub file");
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


/* // THE MESSY MAIN
int main (int argc, char *argv[])
{
	printf("%d", argc);
	printf("this is here for compile %s", argv[0]); 
	
	if (argc != 2)
		err_message_exit("Invalid input.");
	t_game *game;
	
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if(!game)
		err_message_exit("Malloc fail");
	
	//if (argc != 2)
	//	err_message_exit(game, "Invalid input.");
	//if (check_file_extesion(argv[1]))
	//	err_message(game, "please provide a .cub file");
	//parse map
	//init_game(game, argv[1]);
	
	//initializing the MLX library
	game->rays = malloc(sizeof(t_rays));
	if(!game->rays)
		err_message_exit("Failed to malloc for the BEAM\n");
	count_values(game);
	screenpop(game); // opens a window 
	free(game);
	
	//ft_putstr( "for compile");
	
	


	if (check_file_extesion(argv[1]) == 0)
		err_message( "please provide a .cub file");
	//parse map
	
	init_game(game, argv[1]);
	//initializing the MLX library
	//Window Creation


	
	return (0);
}
*/