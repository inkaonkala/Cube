/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:17:58 by iniska            #+#    #+#             */
/*   Updated: 2024/11/14 08:03:42 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static uint32_t	swap_rgb_bgr(uint32_t color)
{
	uint8_t r = (color >> 24) & 0xFF;
	uint8_t g = (color >> 16) & 0xFF;
	uint8_t b = (color >> 8) & 0xFF;
	uint8_t a = color & 0xFF;

	return ((a << 24) | (b << 16) | (g << 8) | r);
}

void	colour_flip(uint32_t *pixels, int width, int height)
{
	int	i;

	i = 0;
	int total_pixels = width * height;
	while (i < total_pixels)
	{
		pixels[i] = swap_rgb_bgr(pixels[i]);
		i++;
	}
}
static int set_t_path(char **map_path, char * t_path)
{
	if (*map_path)
		free(*map_path);
	*map_path = ft_strtrim(t_path, " ");
	if (!*map_path)
	{
		ft_printf("ft_strtrim() failed in set_t_path\n");
		return (1);
	}
	return (0);
}

//int save_colors(t_game *game, char **file_content, t_flag *flags)
int save_colors(t_game *game, char **file_content)
{
	int i;
	int j;

	i = 0;
	while(file_content[i])
	{
		if (empty_line(file_content[i]) == 1)
		{
			i++;
			continue;
		}
		j = 0;
		while(file_content[i][j])
		{
			if (file_content[i][j] == ' ' || file_content[i][j] == '\t')
				j++;
			if (ft_strncmp(file_content[i] + j, "C ", 2) == 0)
			{
				if (set_t_path(&game->ceiling_color, file_content[i] + j + 2) == 1)
					return (1);
				//game->ceiling_color = file_content[i] + j + 2;
			}
			else if (ft_strncmp(file_content[i] + j, "F ", 2) == 0)
			{
				if (set_t_path(&game->floor_color, file_content[i] + j + 2) == 1)
					return (1);
				//game->floor_color = file_content[i] + j + 2;
			}
				
			j++;	
		}
		i++;
	}
	return (0);
}