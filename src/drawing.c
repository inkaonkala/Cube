/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:16:18 by iniska            #+#    #+#             */
/*   Updated: 2024/11/22 09:19:49 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static mlx_texture_t	*backup_box(void)
{
	static mlx_texture_t	*blakkis;
	int						wid;
	int						hei;

	wid = 64;
	hei = 64;
	if (!blakkis)
	{
		blakkis = malloc(sizeof(mlx_texture_t));
		if (!blakkis)
			return (NULL);
		blakkis->width = wid;
		blakkis->height = hei;
		blakkis->pixels = malloc(wid * hei * 4);
		if (!blakkis->pixels)
		{
			free(blakkis);
			return (NULL);
		}
		ft_memset(blakkis->pixels, 0, wid * hei * 4);
	}
	return (blakkis);
}

static mlx_texture_t	*texas(t_game *game)
{
	if (game->rays->wall_flag == true)
	{
		if (game->rays->ray_angl > 0 && game->rays->ray_angl < PI)
			return (game->no_texture);
		else
			return (game->so_texture);
	}
	else
	{
		if (game->rays->ray_angl > PI / 2 && game->rays->ray_angl < 3 * PI / 2)
			return (game->we_texture);
		else
			return (game->ea_texture);
	}
}

static mlx_texture_t	*get_pics_for_wall(t_game *game)
{
	mlx_texture_t	*tex;

	tex = NULL;
	tex = texas(game);
	if (game->hit_door == true)
	{
		check_door(game);
		if (game->door_state == true)
			tex = game->door_open_texture;
		else
			tex = game->door_close_texture;
		game->hit_door = false;
	}
	if (!tex)
		tex = backup_box();
	return (tex);
}

static int	set_y(mlx_texture_t *pic, double top_px, double wall_hi, double y)
{
	y = (top_px - (WIN_HEI / 2) + (wall_hi / 2))
		* (double)pic->height / wall_hi;
	if (y < 0)
		y = 0;
	return (y);
}

void	draw_wall(t_game *game, double bot_px, double top_px, double wall_hi)
{
	mlx_texture_t	*pic;
	uint32_t		*pixels;
	double			x;
	double			y;
	int				pos;

	y = 0.0;
	pic = get_pics_for_wall(game);
	if (!pic || wall_hi <= 0)
		return ;
	pixels = (uint32_t *)pic->pixels;
	x = get_setof_x(game, pic);
	if (x < 0 || x >= pic->width)
		return ;
	y = set_y(pic, top_px, wall_hi, y);
	while (top_px < bot_px)
	{
		pos = (int)y * pic->width + (int)x;
		if (pos < 0 || pos >= (int)(pic->width * pic->height))
			return ;
		mlx_put_pixel(game->canvas, game->rays->i, top_px, pixels[pos]);
		y += (double)pic->height / wall_hi;
		top_px++;
	}
}
