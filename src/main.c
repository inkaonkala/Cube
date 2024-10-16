/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/16 13:24:58 by iniska           ###   ########.fr       */
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

	game = malloc(sizeof(t_game));
	if(!game)
		err_message_exit("Malloc fail");
	memset(game, 0, sizeof(t_game)); // i don't know if we need this
	
	//if (argc != 2)
	//	err_message_exit(game, "Invalid input.");
	//if (check_file_extesion(argv[1]))
	//	err_message(game, "please provide a .cub file");
	//parse map
	//init_game(game, argv[1]);
	//initializing the MLX library
	screenpop(game);
	//raycast(game);

	free(game);


	
	return (0);
}