
#include "../include/cub3D.h"

int find_direction(t_game *game)
{
     dprintf(2, "direction: %f\n", game->rays->ray_angl);
     dprintf(2, "player angled: %f\n", game->player_angl);
    if (game->rays->ray_angl >337.15 || game->player_angl <= 22.5)
        return (0);
    else if (game->rays->ray_angl > 22.5 || game->player_angl <= 67.5)
        return (1);
    else if (game->rays->ray_angl > 67.5 || game->player_angl <= 112.5)
        return (2);
    else if (game->rays->ray_angl > 112.5 || game->player_angl <= 157.5)
        return (3);
    else if (game->rays->ray_angl > 157.5 || game->player_angl <= 202.5)
        return (4);
    else if (game->rays->ray_angl > 202.5 || game->player_angl <= 247.5)
        return (5);
    else if (game->rays->ray_angl > 247.5 || game->player_angl <= 292.5)
        return (6);
    else if (game->rays->ray_angl > 292.5 || game->player_angl <= 337.5)
        return (7);
    else 
        return (-1);
}

void find_texture( t_game * game, float direction)
{
    mlx_texture_t	*player_text;
   
    if (direction == 0)
       player_text = mlx_load_png("./textures/minimap_player_0.png");
    if (direction == 1)
       player_text =  mlx_load_png("./textures/minimap_player_1.png");
    if (direction == 2)
        player_text = mlx_load_png("./textures/minimap_player_2.png");
    if (direction == 3)
       player_text =  mlx_load_png("./textures/minimap_player_3.png");
    if (direction == 4)
       player_text = mlx_load_png("./textures/minimap_player_4.png");
    if (direction == 5)
        player_text = mlx_load_png("./textures/minimap_player_5.png");
    if (direction == 6)
        player_text = mlx_load_png("./textures/minimap_player_6.png");
    if (direction == 7)
        player_text = mlx_load_png("./textures/minimap_player_7.png");

    game->mini_player = mlx_texture_to_image(game->mlx, player_text);
    if (!game->mini_player)
    {
        mlx_strerror(mlx_errno);
		clean_all_exit(game, "mlx_errno");
    }
    mlx_delete_texture(player_text);
}

void draw_player(t_game *game)
{
    long height;
    float direction;
    

    direction = find_direction(game);
    find_texture( game, direction);
    
    height = MINIMAP_SIDE / 2;
    mlx_image_to_window(game->mlx, game->mini_player, (MINIMAP_SIDE / 2) - 8, height - 8);
   
	
    game->mini_player->instances[0].z = 1;// 設置z層，確保渲染順序
    
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int find_minimap_color(t_game *game, int map_x, int map_y)
{
    // 判斷是否在地圖邊界之外，若超出則返回黑色
    if (map_x < 0 || map_y < 0 || map_x >= (int)game->longest || map_y >= (int)game->height)
        return (get_rgba(10, 10, 10, 255));

    if (!game->map || !game->map[map_y]) 
        return (get_rgba(10, 10, 10, 255));

    if (game->map[map_y][map_x] == '1')
        return (get_rgba(40, 26, 13, 255));
       // return (get_rgba(137, 81, 41, 255)); // brown
    else //if (game->map[map_y][map_x] == '0')
        return (get_rgba(230, 224, 193, 255)); // beige

    return (get_rgba(10, 10, 10, 255));
}

int get_minimap_color(t_game *game, int count_x, int count_y)
{
    int start_pos = MINIMAP_TILE_COUNT / 2;
    // int map_x = ((int)game->player_x) - (start_pos - count_x);
    // int map_y = ((int)game->player_y) - (start_pos - count_y);
    int map_x = ((int)game->rays->p_x / TILE) - (start_pos - count_x);
    int map_y = ((int)game->rays->p_y / TILE) - (start_pos - count_y);

    // 確保 map_x 和 map_y 在範圍內
    if (map_x < 0) map_x = 0;
    if (map_y < 0) map_y = 0;
    if (map_x >= (int)game->longest) map_x = game->longest - 1;
    if (map_y >= (int)game->height) map_y = game->height - 1;

    return (find_minimap_color(game, map_x, map_y));
}

void draw_mini_map(t_game *game)
{

    long mini_x;// pixel
    long mini_y;
    int count_x;//pixel
    int count_y;
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

            for (int px = 0; px < MINIMAP_IMAGE_SIDE; px++) 
            {
                for (int py = 0; py < MINIMAP_IMAGE_SIDE; py++) 
                {
                    mlx_put_pixel(game->canvas, mini_x + px, mini_y + py, color);
                }
            }
            count_x++;
        }
        count_y++;
        minimap_line_count++;
    }
    draw_player(game);
}









// int	get_rgba(int r, int g, int b, int a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

// int find_minimap_color(t_game *game, int map_x, int map_y)
// {
//     if (map_x < 0 || map_y < 0 || map_x >= (int)game->longest || map_y >= (int)game->height)
//         return (get_rgba(10, 10, 10, 255));
    
//     // 確保 game->map 和索引都是有效的
//     if (!game->map || !game->map[map_y]) // 注意這裡改成 map_y
//         return (get_rgba(10, 10, 10, 255));

//     //if (game->map[map_x][map_y] == '1')
//     if (game->map[map_x][map_y] == '1')
//         return (get_rgba(137, 81, 41, 255));// brown        
//     else if (game->map[map_x][map_y] == '0')
//         return (get_rgba(230, 224, 193, 255));//beige



//     return (get_rgba(10, 10, 10, 255));
// }



// int  get_minimap_color(t_game *game, int count_x)
// {
//     int start_pos;
//     static int y_counter = 0;
//     int map_x = 0;// unit
//     int map_y = 0;

    
//     dprintf(2, "map dimensions: %zu x %zu\n", game->longest, game->height);
//     dprintf(2, "accessing map[%d][%d]\n", map_y, map_x);    
//     start_pos = MINIMAP_TILE_COUNT / 2;
//     map_x = ((int)game->player_x) - (start_pos - count_x);
//     map_y = ((int)game->player_y) - (start_pos - y_counter);


//      // 添加範圍檢查
//     if (map_x < 0) map_x = 0;
//     if (map_y < 0) map_y = 0;
//     if (map_x >= (int)game->longest) map_x = game->longest - 1;
//     if (map_y >= (int)game->height) map_y = game->height - 1;


//     dprintf(2, "map_x: %d, map_y: %d\n", map_x, map_y);
//     //map_x = (game->rays->p_x / 64) - (start_pos - count_x); 
//     //map_y = (game->rays->p_y / 64) - (start_pos - y_counter); 

//     if (count_x == MINIMAP_TILE_COUNT - 1 )
//         y_counter++;
//     if (y_counter == MINIMAP_TILE_COUNT)
//         y_counter = 0;
//     return (find_minimap_color(game, map_x, map_y));
// }

// void check_minimap_count_x(int *count_x , int *line_count)
// {
//     (*count_x)++;
//     if (*count_x == MINIMAP_TILE_COUNT - 1)
//     {
//         *line_count = *line_count + 1;
//         *count_x = 0;
//     }
    
        
// }


// void draw_mini_map(t_game *game)
// {
//     long mini_x;// pixel
//     long mini_y;
//     int count_x;//pixel
//     int count_y;
//     int minimap_line_count;//紀錄 minimap 橫的是否有１１ 條
//     int color;

//     count_x = 0;
//    dprintf(2, "in draw_mini_map\n");
//     minimap_line_count = 0;
//     while(minimap_line_count < MINIMAP_TILE_COUNT)
//     {
//         mini_x = 0 + (MINIMAP_IMAGE_SIDE * count_x);
//         color = get_minimap_color(game, count_x); 
        
//         dprintf(2, "in draw_mini_map 1\n");

//         while(mini_x < MINIMAP_IMAGE_SIDE * (count_x + 1))//color  minimap tile
//         {
//             dprintf(2, "in draw_mini_map 2\n");

//             mini_y = MINIMAP_IMAGE_SIDE * minimap_line_count;
//             count_y = 0;
            
//             dprintf(2, "in draw_mini_map 3 \n");
//             while(mini_y < MINIMAP_IMAGE_SIDE)
//             {
//                 mlx_put_pixel(game->canvas, mini_x, mini_y, color);
//                 count_y++;
//                 mini_y++;
//             }

//             mini_x++;
//         }
//         dprintf(2, "in draw_mini_map 4 \n");
//         // if (count_x < 11)
//         //     count_x++;
//         // else 
//         // {
//         //     minimap_line_count++;
//         //     count_x = 0;
//         // }
//         check_minimap_count_x(&count_x , &minimap_line_count);
        
//     }
//      dprintf(2, "in draw_mini_map end\n");
//     //c
// }




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

