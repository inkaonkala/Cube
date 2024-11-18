/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:49:10 by iniska            #+#    #+#             */
/*   Updated: 2024/11/18 14:21:01 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	draw_ghosty(t_game *game, int screen_x, int y, double top_pixl, double enemy_hi)
{
	int	src_y;
	int src_x;
	int	x_offset;
	uint32_t pixel_color;
	uint8_t alpha;

	src_y = (int)((y - top_pixl) / enemy_hi * game->enemy->height) + game->enemy->frame_y;
    if (src_y < 0 || src_y >= (int)game->enemy->pic->height)
		return ;
	x_offset = 0;
    while (x_offset < game->enemy->len) 
	{
		src_x = game->enemy->frame_x + x_offset;
		pixel_color = game->enemy->pixels[src_y * game->enemy->pic->width + src_x];
        alpha = (pixel_color >> 24) & 0xFF;
		if (alpha > 0)
        	mlx_put_pixel(game->canvas, screen_x + x_offset, y, pixel_color);
		x_offset++;
	}
}

static void update_pic(t_game *game, int screen_x, double enemy_hi, double top_pixl, double bot_pixl)
{
	int	y;

	y = (int)top_pixl;
	while (y < (int)bot_pixl)
	{
		draw_ghosty(game, screen_x, y, top_pixl, enemy_hi);
		y++;
	}
}

static void update_distance(t_game *game)
{
    size_t		dis_x;
	size_t		dis_y;

	dis_x = (game->enemy->g_x - game->rays->p_x);
	dis_y = (game->enemy->g_y - game->rays->p_y);
	game->enemy->distance = sqrt(dis_x * dis_x + dis_y * dis_y);
}

void update_enemy(t_game *game)
{
    double			enemy_hi;
    double			top_pixl;
    double			bot_pixl;
	int				screen_x;
    
    update_distance(game);
	enemy_hi = fabs((TILE / game->enemy->distance) * (WINDOW_WIDTH) / tan(game->fow));
	if (enemy_hi <= 0)
		return ;
	bot_pixl = (WINDOW_HEIGHT / 2) + (enemy_hi / 2);  // Centered vertically
	top_pixl = (WINDOW_HEIGHT / 2) - (enemy_hi / 2);  // Adjust for half the height
	screen_x = (int)((WINDOW_WIDTH / 2) + (WINDOW_WIDTH) + (game->enemy->angl * WINDOW_WIDTH / FOW)); // It's one TILE off
	game->enemy->frame_x = game->enemy->col * game->enemy->len;
	game->enemy->frame_y = game->enemy->row * game->enemy->height;
    
	update_pic(game, screen_x, enemy_hi, top_pixl, bot_pixl);
}