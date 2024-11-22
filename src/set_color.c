/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:03:23 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/22 17:05:35 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	count_char(char *color, char a)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (color[i])
	{
		if (color[i] == a)
			j++;
		i++;
	}
	return (j);
}

static int	check_rgb_digit(t_game *game, char c)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	if (c == 'f')
		array = game->f_split;
	else
		array = game->c_split;
	while (i < 3)
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] < 48 || array[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_rgb_range(t_game *game)
{
	if (game->floor_r > 255 || game->floor_r < 0)
		return (-1);
	if (game->floor_g > 255 || game->floor_g < 0)
		return (-1);
	if (game->floor_b > 255 || game->floor_b < 0)
		return (-1);
	if (game->ceiling_r > 255 || game->ceiling_r < 0)
		return (-1);
	if (game->ceiling_g > 255 || game->ceiling_g < 0)
		return (-1);
	if (game->ceiling_b > 255 || game->ceiling_b < 0)
		return (-1);
	return (0);
}

void	set_color(t_game *game)
{
	if (count_char(game->ceiling_color, ',') != 2
		|| count_char(game->floor_color, ',') != 2)
		clean_all_exit(game, "wrong color fomat, not with two ','");
	game->c_split = ft_split(game->ceiling_color, ',');
	if (!game->c_split)
		clean_all_exit(game, "c_split split failed.");
	game->f_split = ft_split(game->floor_color, ',');
	if (!game->f_split)
		clean_all_exit(game, "f_split split failed.");
	if (check_rgb_digit(game, 'f') == 1)
		clean_all_exit(game, "floor color format must be digit");
	if (check_rgb_digit(game, 'c') == 1)
		clean_all_exit(game, "ceiling color format must be digit");
	find_color(game->c_split, game->f_split, game);
	free_grid(game->c_split);
	free_grid(game->f_split);
	game->f_split = NULL;
	game->c_split = NULL;
}

void	find_color(char **c_split, char **f_split, t_game *game)
{
	int	i;

	i = -1;
	while (c_split[++i])
	{
		if (i == 0)
			game->ceiling_r = ft_atoi(c_split[i]);
		if (i == 1)
			game->ceiling_g = ft_atoi(c_split[i]);
		if (i == 2)
			game->ceiling_b = ft_atoi(c_split[i]);
	}
	i = 0;
	while (f_split[i])
	{
		if (i == 0)
			game->floor_r = ft_atoi(f_split[i]);
		if (i == 1)
			game->floor_g = ft_atoi(f_split[i]);
		if (i == 2)
			game->floor_b = ft_atoi(f_split[i]);
		i++;
	}
	if (check_rgb_range(game) == -1)
		clean_all_exit(game, "available color range is 0 to 255");
}
