/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:17:58 by iniska            #+#    #+#             */
/*   Updated: 2024/11/08 11:45:44 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static uint32_t invert_rgb(uint32_t color)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	r = ((color >> 24) & 0XFF);
	g = ((color >> 16) & 0XFF);
	b = ((color >> 8) & 0XFF);
	a = color & 0XFF; // 255

	return ((r << 24) | (g << 16) | (b << 8) | a);
	//color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 255;
}

// All the colours seem to be upside down so they eed to be flipped by bytes
void	colour_flip(uint32_t *pixels, int width, int height)
{
	int			total_pixels;
	int			i;
	uint32_t	*pixl;

	i = 0;
	total_pixels = width * height;
	while (i < total_pixels)
	{
			pixl = (uint32_t *)pixels;
			pixl[i] = invert_rgb(pixels[i]);
			i++;
	}

}

static int set_t_path(char **map_t_path, char * t_path)
{
	if (*map_t_path)
		free(*map_t_path);
	*map_t_path = ft_strtrim(t_path, " ");
	if (!*map_t_path)
	{
		err_message("ft_strtrim() failed in set_t_path");
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