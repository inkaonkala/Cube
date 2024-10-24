/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:16:05 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/24 19:40:46 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int only_valid_char(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != '\t' 
				&& map[i][j] != ' ' && map[i][j] != 'N' && map[i][j] != 'S' 
				&& map[i][j] != 'E' && map[i][j] != 'W')
				return (1);
			
			j++;
		}
		
		i++;
	}
	return (0);
}

int eswn_once(char **map)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'N' && map[i][j] == 'S' 
				&& map[i][j] == 'E' && map[i][j] == 'W')
				count++;
			
			j++;
		}
		
		i++;
	}
	return (count);
}


void map_validate(t_game *game)
{
	//map validation: check map size too big too small, empty , invalid char, has NSEW once, if map is closed
	if (game->height > 500 || game->longest > 500)
		clean_all_exit(game, "The map size is tooooo BIG.");
	if (game->height < 3)
		clean_all_exit(game, "The map size is too small.");
	if (only_valid_char(game->map) == 1)
		clean_all_exit(game, "The map has unvalid char.");
	if (eswn_once(game->map) != 1)
		clean_all_exit(game, "EWSN can be used ONLY once.");
	
	//check if map closed
}