/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:16:18 by iniska            #+#    #+#             */
/*   Updated: 2024/11/12 15:37:12 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static mlx_texture_t	*backup_box()
{
	
	static mlx_texture_t	*blakkis;
	int						wid;
	int						hei;

	
	wid = 64;
	hei = 64;
	if(!blakkis)
	{
		blakkis = malloc(sizeof(mlx_texture_t));
		if (!blakkis)
			return (NULL);
		blakkis->width = wid;
		blakkis->height = hei;
		blakkis->pixels = malloc(wid * hei * 4);
		if(!blakkis->pixels)
		{
			free(blakkis);
			return (NULL);
		}
		ft_memset(blakkis->pixels, 0, wid * hei * 4);
	}
	return (blakkis);
}

void	set_pixels(t_game *game, double x, double y, int colour)
{
	if (x < 0)
		return ;
	else if (x >= WINDOW_WIDTH)
		return ;
	if (y < 0)
		return ;
	if (y >= WINDOW_HEIGHT)
		return ;

	mlx_put_pixel(game->canvas, x, y, colour);
}

static double	get_setof_x(t_game *game, mlx_texture_t *pic)
{
	
	//	fmodf finds the remainder of the division, 
	//	so we are returning the spot where the wall need to be
	
	double	x;

	x = 0;
	if (!game || !game->rays || !pic || pic->width == 0)
	{
		printf("No Picture\n");
    	return (x);
	}
	if (game->rays->wall_flag == true)//THIS
		x = (int)fmodf((game->rays->horizon_inter_x * (pic->width / TILE)), pic->width);
	else
		x = (int)fmodf((game->rays->vertical_inter_y * (pic->width / TILE)), pic->width);
	return (x);
}

static mlx_texture_t	*get_pics_for_wall(t_game *game)
{
	mlx_texture_t *tex;

	tex = NULL;
	if (game->rays->wall_flag == true)//THIS
	{
		if (game->rays->ray_angl > 0 && game->rays->ray_angl < PI)
			tex = game->no_texture;
		else
			tex = game->so_texture;
	}
	else
	{
		if (game->rays->ray_angl > PI / 2 && game->rays->ray_angl < 3 * PI / 2)
			tex = game->we_texture;
		else
			tex = game->ea_texture;
	}
	if (!tex)
		tex = backup_box();
	return (tex);
}

void	draw_wall(t_game *game, double bot_pixl, double top_pixl, double wall_hi)
{

	mlx_texture_t	*pic;
	uint32_t		*pixels;
	double			x;
	double			y;
	int				pos;

	pic = get_pics_for_wall(game);
	if (!pic || wall_hi <= 0)
		return ;
	pixels = (uint32_t *)pic->pixels;
	x = get_setof_x(game, pic);
	if (x < 0 || x >- pic->width)
	{
		ft_printf("x out of bounds in draw walls\n");
		return ;
	}
	y = (top_pixl - (WINDOW_HEIGHT / 2) + (wall_hi / 2)) * (double)pic->height / wall_hi;
	if (y < 0)
		y = 0;
	while (top_pixl < bot_pixl)
	{
		pos = (int)y * pic->width + (int)x;
		if (pos < 0 || pos >= (int)(pic->width * pic->height))
			return ;
		mlx_put_pixel(game->canvas, game->rays->i, top_pixl, pixels[pos]);
		y += (double)pic->height / wall_hi;
		top_pixl++;
	}
}
