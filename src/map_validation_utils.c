/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:24:29 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/21 16:37:04 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	flood_fill(char **tmp, int i, int j)
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

static int	if_map_closed(t_game *game, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)game->height)
	{
		j = 0;
		while (tmp[i][j] != '\0')
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

int	check_map_closed(t_game *game, char **map)
{
	char	**tmp;

	tmp = copy_grid(game, map);
	if (!tmp)
		clean_all_exit(game, "The map copy failed.");
	if (if_map_closed(game, tmp) == 1)
	{
		free_grid(tmp);
		return (1);
	}
	free_grid(tmp);
	return (0);
}
