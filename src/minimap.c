/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:41:39 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/15 14:41:40 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int find_minimap_color(t_game *game, int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0 || map_x >= (int)game->longest || map_y >= (int)game->height)
        return (get_rgba(10, 10, 10, 255));

    if (!game->map || !game->map[map_y]) 
        return (get_rgba(10, 10, 10, 255));

    if (game->map[map_y][map_x] == '1')
        return (get_rgba(40, 26, 13, 255));
    else 
        return (get_rgba(230, 224, 193, 255)); // beige

    return (get_rgba(10, 10, 10, 255));
}

static int get_minimap_color(t_game *game, int count_x, int count_y)
{
    int start_pos = MINIMAP_TILE_COUNT / 2;
    int map_x = ((int)game->rays->p_x / TILE) - (start_pos - count_x);
    int map_y = ((int)game->rays->p_y / TILE) - (start_pos - count_y);
    if (map_x < 0) map_x = 0;
    if (map_y < 0) map_y = 0;
    if (map_x >= (int)game->longest) map_x = game->longest - 1;
    if (map_y >= (int)game->height) map_y = game->height - 1;

    return (find_minimap_color(game, map_x, map_y));
}


static void draw_mini_tile(t_game *game, long mini_x, long  mini_y, int color)
{
	int px;
	int py;

	px = 0;
	while ( px < MINIMAP_IMAGE_SIDE) 
	{
		py = 0;
		while (py < MINIMAP_IMAGE_SIDE) 
		{
			mlx_put_pixel(game->canvas, mini_x + px, mini_y + py, color);
			py++;
		}
		px++;
	}
}

void draw_mini_map(t_game *game)
{
    long mini_x;// pixel小地圖上每個方塊的左上角在小地圖中的 x 和 y 座
    long mini_y;
    int count_x;//pixel 計算小地圖中橫向方塊數量。
    int count_y;//計算小地圖中縱向方塊數量。
    int minimap_line_count;//紀錄 minimap 橫的是否有１１ 條
    int color;

    minimap_line_count = 0;
    count_y = 0;
    while (minimap_line_count < MINIMAP_TILE_COUNT)
    {
        count_x = 0;
        while (count_x < MINIMAP_TILE_COUNT)
        {
            mini_x = MINIMAP_IMAGE_SIDE * count_x;
            mini_y = MINIMAP_IMAGE_SIDE * minimap_line_count;
			color = get_minimap_color(game, count_x, count_y);
			draw_mini_tile(game, mini_x, mini_y, color);
            count_x++;
        }
        count_y++;
        minimap_line_count++;
    }
    draw_player(game);
}
