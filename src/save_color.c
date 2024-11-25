/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:17:58 by iniska            #+#    #+#             */
/*   Updated: 2024/11/25 11:27:10 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

uint32_t	swap_rgb_bgr(uint32_t color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	return ((a << 24) | (b << 16) | (g << 8) | r);
}

void	colour_flip(uint32_t *pixels, int width, int height)
{
	int	i;
	int	total_pixels;

	i = 0;
	total_pixels = width * height;
	while (i < total_pixels)
	{
		pixels[i] = swap_rgb_bgr(pixels[i]);
		i++;
	}
}

static int	set_t_path(char **map_path, char *t_path)
{
	if (*map_path)
		free(*map_path);
	*map_path = ft_strtrim(t_path, " ");
	if (!*map_path)
	{
		ft_putendl_fd("ft_strtrim() failed in set_t_path\n", 2);
		return (1);
	}
	return (0);
}

static int	check_color(int i, t_game *game, char **file_content)
{
	int	j;

	j = 0;
	while (file_content[i][j])
	{
		if (file_content[i][j] == ' ' || file_content[i][j] == '\t')
			j++;
		if (ft_strncmp(file_content[i] + j, "C ", 2) == 0)
		{
			if (set_t_path(&game->ceiling_color, file_content[i] + j + 2) == 1)
				return (1);
		}
		else if (ft_strncmp(file_content[i] + j, "F ", 2) == 0)
		{
			if (set_t_path(&game->floor_color, file_content[i] + j + 2) == 1)
				return (1);
		}
		j++;
	}
	return (0);
}

int	save_colors(t_game *game, char **file_content)
{
	int	i;

	i = 0;
	while (file_content[i])
	{
		if (empty_line(file_content[i]) == 1)
		{
			i++;
			continue ;
		}
		if (check_color(i, game, file_content) == 1)
			return (1);
		i++;
	}
	return (0);
}
