/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:40:04 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/31 18:25:58 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


int count_mapline(char **file_content)
{
	int i;

	i = 0;
	while (file_content[i])
		i++;
	return (i);
}

void copy_string( t_game *game, char *s1, char *s2)// s1 map, s2 file content
{
	size_t i;

	i = 0;
	
	while(i < game->longest)
	//while (s2[i])
	{
		if (s2[i])
		{
			if (s2[i] == ' ' || s2[i] == '\t')
				s1[i] = '0';
			else
				s1[i] = s2[i];
		}
		else
			s1[i] = '\0';
		i++;	
	}
	s1[i] = '\0';
}

static int check_longest(char **map_content)
{
	size_t i;
	size_t j;
	size_t l;

	i = 0;
	l = 0;
	while (map_content[i])
	{
		j = 0;
		while (map_content[i][j])
		{
			if (l < j)
				l = j;
			j++;
		}
		i++;
	}
	return (l + 1);
}


int create_map(t_game * game, char **file_content)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	game->longest = check_longest(file_content);
	game->height = count_mapline(file_content);
	
	game->map = (char **)malloc((game->height + 1) * sizeof(char *)); 
	if (game->map == NULL)
		return (1);
	while (file_content[i][0] == '\n' || empty_line(file_content[i]) == 1)
			i++;
	while (file_content[i] && file_content[i][0] != 'N' && file_content[i][0] != 'W' 
		&& file_content[i][0] != 'S' && file_content[i][0] != 'E' 
		&& file_content[i][0] != 'C'&& file_content[i][0] != 'F')
	{
		game->map[j] = (char *) malloc ((game->longest + 1) * sizeof(char));
		//game->map[j] = (char *) calloc ((game->longest + 1), sizeof(char));
		if (game->map[j] == NULL)
		{
			dprintf(2, "Row %d is NULL\n", j);// for test

			return (1);
		}
			
		copy_string(game, game->map[j], file_content[i]);
		i++;
		j++;
	}
	game->map[j] = NULL;
	return (0);
}


void create_rectagle(t_game *game)
{
	size_t k;
	size_t j;
	
	j = 0;
	
	while (game->map[j])
	{
		k = 0;
		while (k < game->longest) 
		{
			// if (game->map[j][k] == ' ' || game->map[j][k] == '\t')
			// 	game->map[j][k] = '1';

			
			if (game->map[j][k] != '1' && game->map[j][k] != '0'
				&& game->map[j][k] != 'E' && game->map[j][k] != 'W'
				&& game->map[j][k] != 'S' && game->map[j][k] != 'N')
				game->map[j][k] = '1';

			// if (game->map[j][k] == 'k')
			// 	game->map[j][k] = '1';
			k++;
		}
		game->map[j][k] = '\0';
		j++;
	}
}