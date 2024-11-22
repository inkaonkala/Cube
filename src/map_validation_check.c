/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:16:05 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/21 16:35:29 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	only_valid_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
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

static int	eswn_once(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
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

char	**copy_grid(t_game *game, char **map)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = (char **)(malloc((game->height + 1) * sizeof(char *)));
	if (result == NULL)
		return (NULL);
	while (map[i])
	{
		result[j] = (char *) calloc ((game->longest + 1), sizeof(char));
		if (result[j] == NULL)
		{
			while (j > 0)
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

void	map_validate(t_game *game)
{
	if (game->height > 500 || game->longest > 500)
		clean_all_exit(game, "The map size is tooooo BIG.");
	if (game->height < 3)
		clean_all_exit(game, "The map size is too small.");
	if (only_valid_char(game->map) == 1)
		clean_all_exit(game, "The map has invalid char.");
	if (eswn_once(game->map) != 1)
		clean_all_exit(game, "EWSN can be used once and ONLY once.");
	if (check_map_closed(game, game->map) == 1)
		clean_all_exit(game, "This map is not enclosed.");
}
