
#include "../include/cub3D.h"


void check_door_position(t_game *game, char ** map)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				count++;
				game->door_x = j;
				game->door_y = i;
			}
			j++;
		}
		i++;
	}
	if (count > 1)
		clean_all_exit(game, "only ONE door is allowed.");
     //dprintf(2, "in position check door x: %zu, door y : %zu\n", game->door_x, game->door_y);
}


void init_door(t_game *game)
{
    
	if(game->door_state != true)
		game->door_state = false;
    game->hit_door = false;
	game->d = '\0';
    check_door_position(game, game->map);

    game->door_open_texture = mlx_load_png(DOOR_PATH_OPEN);
    if (game->door_open_texture)
		colour_flip((uint32_t *)game->door_open_texture->pixels, game->door_open_texture->width, game->door_open_texture->height);

	
    if (!game->door_open_texture)
    {
        mlx_strerror(mlx_errno);
		clean_all_exit(game, "mlx_png_err");
    }
    game->door_close_texture = mlx_load_png(DOOR_PATH_CLOSE);
	 if (game->door_close_texture)
		colour_flip((uint32_t *)game->door_close_texture->pixels, game->door_close_texture->width, game->door_close_texture->height);

    if (!game->door_close_texture)
    {
        mlx_strerror(mlx_errno);
		clean_all_exit(game, "mlx_png_err");
    }
}

void check_door(t_game *game)
{
    float distance;
    int dx;
    int dy;
    
    dx = (game->rays->p_x / TILE)- game->door_x;
    dy = (game->rays->p_y / TILE)- game->door_y;
    distance = sqrt((dx * dx) + (dy * dy));
	//dprintf(2, "px:%d, py:%d dx:%zu, dy:%zu\n", (game->rays->p_x / TILE),(game->rays->p_y / TILE),game->door_x,game->door_y);
	//dprintf(2, "distance: %f\n", distance);
 	 if (distance < 1.43 && game->d == 'D')
    {
	}
   
   if (distance < 1.43 && game->d == 'D')
    {
       
		if (game->door_state == false)
		{
		//dprintf(2, "game->d: %c \n", game->d);
			game->door_state = true;
		}
    }
	else if (distance > 1.5)
		game->door_state = false;       
}