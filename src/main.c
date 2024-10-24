/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/24 15:20:59 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"

#include <stdio.h>

int main (int argc, char *argv[])
{
	
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


	
	return (0);
}