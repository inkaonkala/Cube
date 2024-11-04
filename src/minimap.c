
#include "../include/cub3D.h"



void draw_mini_map(t_game *game)
{
	
}



// int	color(int r, int g, int b, int a)
// {
// 	if (r >= 0 && g >= 0 && b >= 0 && a >= 0
// 		&& r <= 255 && g <= 255 && b <= 255 && a <= 255)
// 		return (r << 24 | g << 16 | b << 8 | a);
// 	if (r < 0)
// 		return (color(0, g, b, a));
// 	if (g < 0)
// 		return (color(r, 0, b, a));
// 	if (b < 0)
// 		return (color(r, g, 0, a));
// 	if (a < 0)
// 		return (color(r, g, b, 0));
// 	if (r > 255)
// 		return (color(255, g, b, a));
// 	if (g > 255)
// 		return (color(r, 255, b, a));
// 	if (b > 255)
// 		return (color(r, g, 255, a));
// 	return (color(r, g, b, 255));
// }


// int is_wall(t_game *game, int x, int y)
// {
//     float x_minimap_to_loc;
//     float y_minimap_to_loc;
//     //float scale = MINIMAP_SIDE / (float)MINIMAP_COVERAGE;
//     // 計算小地圖上的 (x, y) 坐標轉換為遊戲地圖的實際座標
//      x_minimap_to_loc = x - 0.5 - MINIMAP_COVERAGE / 2
//          + (x + (MINIMAP_SIDE / (2 * MINIMAP_COVERAGE))) / (MINIMAP_SIDE / MINIMAP_COVERAGE);
//      y_minimap_to_loc = y - 0.5 - MINIMAP_COVERAGE / 2
//          + (y + (MINIMAP_SIDE / (2 * MINIMAP_COVERAGE))) / (MINIMAP_SIDE / MINIMAP_COVERAGE);

//     // 小地圖的 (minimap_x, minimap_y) 轉換為遊戲地圖座標 (game_x, game_y)
//     //x_minimap_to_loc = (x - MINIMAP_PADDING) / scale + game->rays->p_x - MINIMAP_COVERAGE / 2;
//    // y_minimap_to_loc = (y - MINIMAP_PADDING) / scale + game->rays->p_y - MINIMAP_COVERAGE / 2;


//     //x_minimap_to_loc = x * MINIMAP_COVERAGE;
//     //y_minimap_to_loc = y * MINIMAP_COVERAGE;
//     dprintf(2, "x_minimap_to_loc: %f,y_minimap: %f\n",x_minimap_to_loc,y_minimap_to_loc);
//     // 檢查是否超出地圖邊界
//     if (x_minimap_to_loc < 0 || x_minimap_to_loc >= (int)game->longest ||
//         y_minimap_to_loc < 0 || y_minimap_to_loc >= (int)game->height)
//     {
//         return (0); // 超出邊界，視為沒有牆壁
//     }

//     // 檢查是否為牆
//     // if (game->map[(int)x_minimap_to_loc][(int)y_minimap_to_loc] == '1')
//     // {
//     //     return (1); // 該位置為牆壁
//     // }

//     return (0); // 該位置不是牆壁
// }

// void create_minimap(t_game *game)
// {
// 	int minifloor_color;// 白色，半透明
// 	int miniwall_color;// 黑色，不透明

// 	int i;
// 	int j;
// 	//int scaled_x;
//     //int scaled_y;

// 	i = 0;
// 	minifloor_color = color(255, 255, 255, 150);
// 	miniwall_color = color(0, 0, 0, 255);
	
// 	game->minimap = mlx_new_image(game->mlx, MINIMAP_SIDE, MINIMAP_SIDE);
//     //game->minimap = mlx_new_image(game->mlx, game->longest/MINIMAP_COVERAGE, game->height/MINIMAP_COVERAGE);
// 	if (!game->minimap) 
// 	{
//         mlx_terminate(game->mlx);
//         clean_all_exit(game, "Minimap creation failed");
//     }
	
// 	    // 遍歷地圖數據並繪製小地圖
//     while (i < MINIMAP_SIDE)
//     //while (i < (int)game->height/MINIMAP_COVERAGE)
//     {
//         j = 0;
//         while (j < MINIMAP_SIDE)
//         //while(j < (int)game->longest/MINIMAP_COVERAGE)
//         {
//             //將小地圖像素坐標轉換為遊戲地圖的坐標
//             //int map_x = (i * MINIMAP_COVERAGE / MINIMAP_SIDE) + game->rays->p_x - MINIMAP_COVERAGE / 2;
//             //int map_y = (j * MINIMAP_COVERAGE / MINIMAP_SIDE) + game->rays->p_y - MINIMAP_COVERAGE / 2;

//             // 檢查是否為牆壁
//             if (is_wall(game, i, j) == 1)
//                 mlx_put_pixel(game->minimap, i, j, miniwall_color);
//             else
//                 mlx_put_pixel(game->minimap, i, j, minifloor_color);
//             j++;    
//         }
//         i++;
//     }
// 	mlx_image_to_window(game->mlx, game->minimap, MINIMAP_PADDING, MINIMAP_PADDING);
// 	game->minimap->instances[0].z = 1;// 設置z層，確保渲染順序

// }

