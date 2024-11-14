
#include "../include/cub3D.h"

static int find_direction(t_game *game)
{
    if (game->mini_angle > 4.3186 && game->mini_angle <= 5.1038)
        return (0);
    else if (game->mini_angle > 5.1038 && game->mini_angle <= 6.3)
        return (1);
    else if (game->mini_angle > 5.889 || game->mini_angle <= 0.3926)
        return (2);
    else if (game->mini_angle > 0.3926 && game->mini_angle <= 1.1778)
        return (3);
    else if (game->mini_angle > 1.1778 && game->mini_angle <= 1.963)
        return (4);
    else if (game->mini_angle > 1.963 && game->mini_angle <= 2.7482)
        return (5);
    else if (game->mini_angle > 2.7482 && game->mini_angle <= 3.5334)
        return (6);
    else if (game->mini_angle > 3.5334 && game->mini_angle <= 4.3186)
        return (7);
  return (-1);
}

static void find_texture( t_game * game, float direction)
{
    mlx_texture_t	*player_text;
    player_text = NULL;
	if (direction == 0)
       player_text = mlx_load_png("./textures/minimap_player_0.png");
    else if (direction == 1)
    	player_text =  mlx_load_png("./textures/minimap_player_1.png");
    else if (direction == 2)
        player_text = mlx_load_png("./textures/minimap_player_2.png");
    else if (direction == 3)
       player_text =  mlx_load_png("./textures/minimap_player_3.png");
    else if (direction == 4)
       player_text = mlx_load_png("./textures/minimap_player_4.png");
   	else if (direction == 5)
        player_text = mlx_load_png("./textures/minimap_player_5.png");
    else if (direction == 6) 
        player_text = mlx_load_png("./textures/minimap_player_6.png");
    else if (direction == 7)
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
    game->mini_player->instances[0].z = 1;
}