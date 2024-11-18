/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:49:10 by iniska            #+#    #+#             */
/*   Updated: 2024/11/18 09:25:11 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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