/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/21 09:37:39 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int check_file_extesion(char *filename)
{
	int len;
	
	len = ft_strlen(filename);
	if (len <= 4 || ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
		return (0); 
	return (1); //filename with .cub
}


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


	
	return (0);
}