/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/15 20:34:06 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


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
	t_game *game;
	
	if (argc != 2)
		err_message_exit(game, "Invalid input.");
	if (check_file_extesion(argv[1]))
		err_message(game, "please provide a .cub file");
	//parse map
	init_game(game, argv[1]);
	//initializing the MLX library
	// Window Creation
	//raycast(game);




	
	return (0);
}