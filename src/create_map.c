/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:40:04 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/24 18:20:04 by yhsu             ###   ########.fr       */
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
void copy_string(t_game *game, char *s1, char *s2)// s1 map, s2 file content
{
	size_t i;

	i = 0;
	while(i < game->longest + 1)
	{
		if (s2[i])
			s1[i] = s2[i];
		else
			s1[i] = '\0';
		i++;	
	}
	
}

int check_longest(char **map_content)
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
	//dprintf(2, "game->longest: %d\n", game->longest);
	game->height = count_mapline(file_content);
	dprintf(2, "game->height: %zu\n",game->height);
	game->map = (char **)malloc((game->height + 1) * sizeof(char *)); 
	if (game->map == NULL)
		return (1);
	while (file_content[i][0] == '\n' || empty_line(file_content[i]) == 1)
			i++;
	while (file_content[i] && file_content[i][0] != 'N' && file_content[i][0] != 'W' 
		&& file_content[i][0] != 'S' && file_content[i][0] != 'E' 
		&& file_content[i][0] != 'C'&& file_content[i][0] != 'F')
	{
		game->map[j] = (char *) malloc (game->longest * sizeof(char));
		if (game->map[j] == NULL)
			return (1);
		copy_string(game, game->map[j],file_content[i]);
		i++;
		j++;
	}
	game->map[j] = NULL;
	return (0);
}

// int	count_2darray_size(char **src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i] != NULL)
// 		i++;
// 	return (i);
// }

// static int	copy_string(char **copy, char *src, int i)
// {
// 	int	j;

// 	copy[i] = malloc(sizeof(char) * (ft_strlen(src) + 1));
// 	if (!copy[i])
// 		return (0);
// 	j = 0;
// 	while (src[j] != '\0')
// 	{
// 		copy[i][j] = src[j];
// 		j++;
// 	}
// 	copy[i][j] = '\0';
// 	return (1);
// }

// char	**copy_2darray(char **src)
// {
// 	char	**copy;
// 	int		size;
// 	int		i;

// 	i = 0;
// 	size = count_2darray_size(src);
// 	copy = malloc(sizeof(char *) * (size + 1));
// 	if (!copy)
// 		return (NULL);
// 	while (src[i] != NULL)
// 	{
// 		if (!copy_string(copy, src[i], i))
// 		{
// 			while (i > 0)
// 				free(copy[--i]);
// 			free(copy);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

// char	**create_map(char **file_copy)
// {
// 	char	**map;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	map = copy_2darray(file_copy);
// 	if (!map)
// 		return (NULL);
// 	while (file_copy[i] != NULL)
// 	{
// 		j = 0;
// 		while (file_copy[i][j] != '\0')
// 		{
// 			if (file_copy[i][j] == ' ' || file_copy[i][j] == '\t')
// 				map[i][j] = '1';
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (map);
// }