/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:49:10 by iniska            #+#    #+#             */
/*   Updated: 2024/11/19 10:11:51 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	draw_ghosty(t_game *game, int screen_x, int y, double top_pixl, double g_hi)
{
	int	src_y;
	int src_x;
	int	x_offset;
	uint32_t pixel_color;
	uint8_t alpha;

	src_y = (int)((y - top_pixl) / g_hi * game->g->height) + game->g->frame_y;
    if (src_y < 0 || src_y >= (int)game->g->pic->height)
		return ;
	x_offset = 0;
    while (x_offset < game->g->len) 
	{
		src_x = game->g->frame_x + x_offset;
		pixel_color = game->g->pixels[src_y * game->g->pic->width + src_x];
        alpha = (pixel_color >> 24) & 0xFF;
		if (alpha > 0)
        	mlx_put_pixel(game->canvas, screen_x + x_offset, y, pixel_color);
		x_offset++;
	}
}

static void update_pic(t_game *game, int screen_x, double g_hi, double top_pixl, double bot_pixl)
{
	int	y;

	y = (int)top_pixl;
	while (y < (int)bot_pixl)
	{
		draw_ghosty(game, screen_x, y, top_pixl, g_hi);
		y++;
	}
}

static void update_distance(t_game *game)
{
    size_t		dis_x;
	size_t		dis_y;

	dis_x = (game->g->g_x - game->rays->p_x);
	dis_y = (game->g->g_y - game->rays->p_y);
	game->g->distance = sqrt(dis_x * dis_x + dis_y * dis_y);
}

void update_g(t_game *game)
{
    double			g_hi;
    double			top_pixl;
    double			bot_pixl;
	int				screen_x;
    
    update_distance(game);
	g_hi = fabs((TILE / game->g->distance) * (WIN_WIDTH) / tan(game->fow));
	if (g_hi <= 0)
		return ;
	bot_pixl = (WIN_HEI / 2) + (g_hi / 2);  // Centered vertically
	top_pixl = (WIN_HEI / 2) - (g_hi / 2);  // Adjust for half the height
	screen_x = (int)((WIN_WIDTH / 2) + (WIN_WIDTH) + (game->g->angl * WIN_WIDTH / FOW)); // It's one TILE off
	game->g->frame_x = game->g->col * game->g->len;
	game->g->frame_y = game->g->row * game->g->height;
    update_pic(game, screen_x, g_hi, top_pixl, bot_pixl);
}