/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:16:05 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/18 18:49:21 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int only_valid_char(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])// mendatory need to remove D
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != '\t' 
				&& map[i][j] != ' ' && map[i][j] != 'N' && map[i][j] != 'S' 
				&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != 'D')
				return (1);
			
			j++;
		}
		
		i++;
	}
	return (0);
}

static int eswn_once(char **map)
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
			if (map[i][j] == 'N' || map[i][j] == 'S' 
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				count++;
			}
				
			
			j++;
		}
		
		i++;
	}
	return (count);
}

char **copy_grid(t_game *game, char **map)
{
	int i;
	int j;
	char **result;

	i = 0;
	j = 0;
	result = (char **)(malloc((game->height + 1) * sizeof(char *)));
	if (result == NULL)
		return (NULL);
	while(map[i])
	{
		result[j] = (char *) calloc ((game->longest + 1), sizeof(char));
		if (result[j] == NULL)
		{
			while(j > 0)
				free(result[--j]);
			free(result);
			return (NULL);
		}
		copy_string(result[j], map[i]);
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

static int flood_fill(char **tmp, int i, int j)// open return 1
{
	if (i < 0 || j < 0 || !tmp[i] || !tmp[i][j])
		return (1);
	if (tmp[i][j] == '1' || tmp[i][j] == 'D')
		return (0);
	tmp[i][j] = '1';
	if (flood_fill(tmp, i + 1, j) != 0)
		return (1);
	if (flood_fill(tmp, i - 1, j) != 0)
		return (1);
	if (flood_fill(tmp, i, j + 1) != 0)
		return (1);
	if (flood_fill(tmp, i, j - 1) != 0)
		return (1);
	return (0);
}

static int if_map_closed(t_game *game, char **tmp)// open return 1
{
	int i;
	int j;

	i = 0;
	//while (tmp[i] != (void *)'\0')
	while (i < (int)game->height)
	{
		j = 0;
		while(tmp[i][j] != '\0')
		{
			if ((tmp[i][j] == 'S' || tmp[i][j] == 'E'
				|| tmp[i][j] == 'W' || tmp[i][j] == 'N' || tmp[i][j] == '0'))
			{
				if (flood_fill(tmp, i, j) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


static int check_map_closed(t_game *game, char **map)
{
	char **tmp;
	
	tmp = copy_grid(game, map);

	if (!tmp)
		clean_all_exit(game, "The map copy failed.");
	if (if_map_closed(game, tmp) == 1)
	{
		ft_putendl_fd("map not closed\n", 2);//change to error message 
		free_grid(tmp);
		return (1);//the map is open
	}

	free_grid(tmp);
	return (0);
}

void map_validate(t_game *game)
{
	
	//map validation: check map size too big too small, empty , invalid char, has NSEW once, if map is closed
	if (game->height > 500 || game->longest > 500)
		clean_all_exit(game, "The map size is tooooo BIG.");
	
	if (game->height < 3)
		clean_all_exit(game, "The map size is too small.");
	
	if (only_valid_char(game->map) == 1)
		clean_all_exit(game, "The map has invalid char.");
	
	if (eswn_once(game->map) != 1)
		clean_all_exit(game, "EWSN can be used once and ONLY once.");
	//check if map closed

	if (check_map_closed(game, game->map) == 1)
		clean_all_exit(game, "This map is not enclosed.");


}