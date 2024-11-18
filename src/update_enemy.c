/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:49:10 by iniska            #+#    #+#             */
/*   Updated: 2024/11/18 10:47:24 by iniska           ###   ########.fr       */
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

                // Draw pixel if not transparent
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

void update_enemy(t_game *game)
{
    double			enemy_hi;
    double			top_pixl;
    double			bot_pixl;
	int				screen_x;
	
	enemy_hi = fabs((TILE / game->enemy->distance) * (WINDOW_WIDTH) / tan(FOW));
	if (enemy_hi <= 0)
		return ;
	bot_pixl = (WINDOW_HEIGHT / 2) + (enemy_hi / 2);  // Centered vertically
	top_pixl = (WINDOW_HEIGHT / 2) - (enemy_hi / 2);  // Adjust for half the height
	screen_x = (int)((WINDOW_WIDTH / 2) + (game->enemy->angl * WINDOW_WIDTH / game->fow)); // It's one TILE off
//	y = (int)(top_pixl);
	game->enemy->frame_x = game->enemy->col * game->enemy->len;
	game->enemy->frame_y = game->enemy->row * game->enemy->height;
    
	update_pic(game, screen_x, enemy_hi, top_pixl, bot_pixl);
}

/*
void update_enemy(t_game *game)
{
    double enemy_hi;
    double top_pixl;
    double bot_pixl;
    int screen_x;
	int y;
    mlx_texture_t *pic = game->enemy->ghost_sheet;
    uint32_t *pixels = (uint32_t *)pic->pixels;
    
    enemy_hi = fabs((TILE / game->enemy->distance) * (WINDOW_WIDTH) / tan(FOW));
    bot_pixl = (WINDOW_HEIGHT / 2) + (enemy_hi / 2);  // Centered vertically
    top_pixl = (WINDOW_HEIGHT / 2) - (enemy_hi / 2);  // Adjust for half the height
    screen_x = (int)((WINDOW_WIDTH / 2) + (game->enemy->angl * WINDOW_WIDTH / game->fow)); // It's one TILE off
    y = (int)(top_pixl);

    // Get the current frame position in the sprite sheet
    int frame_x = game->enemy->col * game->enemy->len;
    int frame_y = game->enemy->row * game->enemy->height;
    
    // Render enemy in vertical slices
    while (y < (int)bot_pixl) 
	{
        int src_y = (int)((y - top_pixl) / enemy_hi * game->enemy->height) + frame_y;
        
        if (src_y >= 0 && src_y < (int)pic->height) 
		{
			int x_offset = 0;
            while (x_offset < game->enemy->len) 
			{
                int src_x = frame_x + x_offset;
                uint32_t pixel_color = pixels[src_y * pic->width + src_x];
                uint8_t alpha = (pixel_color >> 24) & 0xFF;

                // Draw pixel if not transparent
                if (alpha > 0) {
                    mlx_put_pixel(game->canvas, screen_x + x_offset, y, pixel_color);
                }
				x_offset++;
            }
        }
		y++;
    }
}
*/