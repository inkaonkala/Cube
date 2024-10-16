/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:02:51 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/15 18:24:03 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


// init_game(t_game *game, char *mapfile)
// {
// 	//parse file : create sd array map,  parse element
// 	//map validation: check map size too big too small, empty , invalid char, has NSEW once, if map is closed
	
// 	//get position 
// }

int check_file_extesion(char *filename)
{
	int len;
	
	len = ft_strlen(filename);
	if (len <= 4 || ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
		return (0); 
	return (1); //filename with .cub
}



