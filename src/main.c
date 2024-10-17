/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/17 19:47:52 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"



int main (int argc, char *argv[])
{
	
	//ft_putstr( "for compile");
	
	t_game *game;

	if (argc != 2)
		err_message_exit("Invalid input.");
	//ft_bzero(game, sizeof(t_game));
	game = calloc(1, sizeof(t_game));
	if(!game)
		err_message_exit("Malloc fail");

	if (check_file_extesion(argv[1]) == 0)
		err_message( "please provide a .cub file");
	//parse map
	init_game(game, argv[1]);
	//initializing the MLX library
	//Window Creation


	
	return (0);
}