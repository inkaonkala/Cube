
#include "../include/cub3D.h"

void	fill_background(t_game *game)
{
	size_t	x;
	size_t	y;
dprintf(2, "in fill_background 0\n");
	y = 0;
	while (y < game->height)
	{
		dprintf(2, "in fill_background 1\n");
        x = 0;
		while (x < game->longest)
		{
			if (mlx_image_to_window(game->mlx, game->minifloor,
					x * PIXELS, y * PIXELS) < 0)
				clean_all_exit(game, "Failed to put image to window");
			x++;
		}
		y++;
	}
    //dprintf(2, "in fill_background 2\n");
}

void init_minimap(t_game *game)
{
    // add texture
    mlx_texture_t	*minifloor;
    mlx_texture_t	*miniwall;
    mlx_texture_t	*miniplayer;
    game->mlx = mlx_init(300,300,"Mini Map", false);
    if (!game->mlx)
        clean_all_exit(game, "Failed to initialize mlx");
    dprintf(2, "in init minimap 1\n");
    minifloor = mlx_load_png("./textures/minifloor.png");
    if (!minifloor)
		clean_all_exit(game, "Problem with loading minifloor");
    game->minifloor = mlx_texture_to_image(game->mlx, minifloor);
    if (!game->minifloor)
		clean_all_exit(game, "Problem with texture to game->minifloor");
    mlx_delete_texture (minifloor);
dprintf(2, "in init minimap2 \n");
    miniwall = mlx_load_png("./textures/miniwall.png");
    if (!miniwall)
		clean_all_exit(game, "Problem with loading miniwall");
    game->miniwall = mlx_texture_to_image(game->mlx, miniwall);
    if (!game->miniwall)
		clean_all_exit(game, "Problem with texture to game->miniwall");
    mlx_delete_texture (miniwall);
dprintf(2, "in init minimap 3\n");
    miniplayer = mlx_load_png("./textures/miniplayer.png");
    if (!miniplayer)
		clean_all_exit(game, "Problem with loading miniplayer");
    game->miniplayer = mlx_texture_to_image(game->mlx, miniplayer);
    if (!game->miniplayer)
		clean_all_exit(game, "Problem with texture to game->miniplayer");
    mlx_delete_texture (miniplayer);
dprintf(2, "in init minimap 4\n");
    fill_background(game);
dprintf(2, "in init minimap 5\n");
}

void	image_select(t_game *game, size_t y, size_t x)
{
	//size_t	image_size = 32;
    dprintf(2, "in image_select 0\n");
	if (game->map[y][x] == '1')
		if (mlx_image_to_window(game->mlx, game->miniwall,
				x * PIXELS, y * PIXELS) < 0)
			clean_all_exit(game, "failed to load image(miniwall) to window");
	if (game->map[y][x] != '1' )
		if (mlx_image_to_window(game->mlx, game->minifloor,
				x * PIXELS, y * PIXELS) < 0)
			clean_all_exit(game, "failed to load image(minifloor) to window");
	
	// if (game->map[y][x] == 'E')
	// 	if (mlx_image_to_window(game->mlx, data->,
	// 			x * PIXELS, y * PIXELS) < 0)
	// 		error_message("failed to load image(gravestone) to window", data);
}

void render_minimap(t_game * game)
{
    size_t	x;
	size_t	y;

	x = 0;
	y = 0;

    dprintf(2, "in render_minimap 0\n");
	while (y < game->height)
	{
		x = 0;
		while (x < game->longest)
		{
			image_select(game, y, x);
			x++;
		}
		y++;
	}
    dprintf(2, "in render_minimap 2\n");
}

t_game	*move_left(t_game *game)
{
	if (game->map[game->player_y][game->player_x - 1] != '1'
		&& game->map[game->player_y][game->player_x - 1] != 'E')
	{
		if (game->map[game->player_y][game->player_x - 1] == 'C')
		{
			
			game->map[game->player_y][game->player_x - 1] = '0';
			
		}
		game->player_x -= 1;
		game->miniplayer->instances[0].x -= 1 * PIXELS;
		
	}
	//check_game_status(game);
	return (game);
}

t_game	*move_right(t_game *game)
{
	if (game->map[game->player_y][game->player_x + 1] != '1'
		&& game->map[game->player_y][game->player_x + 1] != 'E')
	{
		if (game->map[game->player_y][game->player_x + 1] == 'C')
		{
			
			
			
			game->map[game->player_y][game->player_x + 1] = '0';
		}
		game->player_x += 1;
		game->miniplayer->instances[0].x += 1 * PIXELS;
		
	}
	//check_game_status(game);
	return (game);
}

t_game	*move_up(t_game *game)
{
	if (game->map[game->player_y - 1][game->player_x] != '1'
		&& game->map[game->player_y - 1][game->player_x] != 'E')
	{
		if (game->map[game->player_y - 1][game->player_x] == 'C')
		{
			
			
			game->map[game->player_y - 1][game->player_x] = '0';
        }
		game->player_y -= 1;
		game->miniplayer->instances[0].y -= 1 * PIXELS;
	
	}
	//check_game_status(game);
	return (game);
}


t_game	*move_down(t_game *game)
{
	if (game->map[game->player_y + 1][game->player_x] != '1'
		&& game->map[game->player_y + 1][game->player_x] != 'E')
	{
		if (game->map[game->player_y + 1][game->player_x] == 'C')
		{
			game->map[game->player_y + 1][game->player_x] = '0';
			
		}
		game->player_y += 1;
		game->miniplayer->instances[0].y += 1 * PIXELS;
	}
	//check_game_status(game);
	return (game);
}

void	move_select(t_game *game, char line, char direction)
{
	if (line == 'y')
	{
		if (direction == 'u')
			move_up(game);
		else
			move_down(game);
	}
	if (line == 'x')
	{
		if (direction == 'r')
			move_right(game);
		else
			move_left(game);
	}
}



void	load_player( t_game *game, char direction)
{
	if (direction == 'u')
        mlx_put_pixel(game->miniplayer, game->player_x, game->player_y, 0xFF0000FF);
        //mlx_draw_pixel(5, 0xBB4211);
		//mlx_draw_texture(game->miniplayer, mlx_load_png("./textures/miniplayer.png"), 0, 0);
	if (direction == 'd')
		mlx_put_pixel(game->miniplayer, game->player_x, game->player_y, 0xFF0000FF);
        //mlx_draw_texture(game->miniplayer, mlx_load_png("./textures/miniplayer.png"), 0, 0);
	if (direction == 'r')
		mlx_put_pixel(game->miniplayer, game->player_x, game->player_y, 0xFF0000FF);
        //mlx_draw_texture(game->miniplayer, mlx_load_png("./textures/miniplayer.png"), 0, 0);
	if (direction == 'l')
		mlx_put_pixel(game->miniplayer, game->player_x, game->player_y, 0xFF0000FF);
        //mlx_draw_texture(game->miniplayer, mlx_load_png("./textures/miniplayer.png"), 0, 0);
   
}

void	move_player(t_game *game, char line, char direction)
{
	  dprintf(2, "move_player\n");
    move_select(game, line, direction);
     dprintf(2, "move_player 1\n");
	load_player(game, direction);
 dprintf(2, "move_player 2\n");
}

void	move_hook(mlx_key_data_t keydata, void *data)
{
	t_game	*game;
    dprintf(2, "in move hook\n");
	game = (t_game *)data;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_player(game, 'y', 'u');
    dprintf(2, "in move hook 0\n");
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_player(game, 'y', 'd');
    dprintf(2, "in move hook 1\n");
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_player(game, 'x', 'r');
    dprintf(2, "in move hook 2\n");
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_player(game, 'x', 'l');
}