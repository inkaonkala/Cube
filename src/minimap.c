
#include "../include/cub3D.h"

int find_direction(t_game *game)
{

    if(game->s == 'N')
        return (0);
    else
        return (4);
/*
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
   */

}

void find_texture( t_game * game, float direction)
{
    mlx_texture_t	*player_text;
   
    if (direction == 0)
       player_text = mlx_load_png("./textures/minimap_player_0.png");
    // if (direction == 1)
    //    player_text =  mlx_load_png("./textures/minimap_player_1.png");
    if (direction == 2)
        player_text = mlx_load_png("./textures/minimap_player_2.png");
    // if (direction == 3)
    //    player_text =  mlx_load_png("./textures/minimap_player_3.png");
    if (direction == 4)
       player_text = mlx_load_png("./textures/minimap_player_4.png");
    // if (direction == 5)
    //     player_text = mlx_load_png("./textures/minimap_player_5.png");
    if (direction == 6)
        player_text = mlx_load_png("./textures/minimap_player_6.png");
    // if (direction == 7)
    //     player_text = mlx_load_png("./textures/minimap_player_7.png");

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

void loop_map(t_game *game, long mini_x, long mini_y, int color)
{
	int px = 0;
	int py = 0;

	px = 0;
	py = 0;
	while ( px < MINIMAP_IMAGE_SIDE) 
	{
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



