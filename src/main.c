/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:09 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/22 09:30:22 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
		err_message_exit("Invalid input.");
	if (check_file_extesion(argv[1]) == 0)
		err_message_exit("please provide a correct '.cub' file");
	game = calloc(1, sizeof(t_game));
	if (!game)
		err_message_exit("Malloc failed");
	init_game(game, argv[1]);
	game->rays = malloc(sizeof(t_rays));
	if (!game->rays)
		err_message_exit("Failed to malloc for the BEAM\n");
	count_values(game);
	screenpop(game);
	clean_all(game);
	return (0);
}
