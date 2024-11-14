/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghostie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:49:31 by iniska            #+#    #+#             */
/*   Updated: 2024/11/08 10:36:44 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_enemy(t_game *game, int frame_w, int frame_l)
{
	uint32_t 	*pixels;
	int			x;
	int			y;
	int			dest_x = 0;
	int			dest_y = 0;
	int			src_pos;

	pixels = (uint32_t *)game->enemy->ghost_sheet->pixels;
	game->enemy->x_offset = game->enemy->col * frame_w;
	game->enemy->y_offset = game->enemy->row * frame_l;
	y = 0;
	while(y < frame_l)
	{
		x = 0;
		while (x < frame_w)
		{
			src_pos = (game->enemy->y_offset + y) * game->enemy->ghost_sheet->width + (game->enemy->x_offset + x);
			game->enemy->color = pixels[src_pos];
			mlx_put_pixel(game->enemy->ghosty, dest_x + x, dest_y + y, game->enemy->color);
			x++;
		}
		y++;
	}
}

static void	animate(t_game *game)
{
	static int frame_counter = 0;

	game->enemy->height = 423 / 8;
	game->enemy->len = 432 / 12;

	game->enemy->row = frame_counter / 12;
	game->enemy->col = frame_counter % 12;

	frame_counter++;
	if(frame_counter >= 96)
		frame_counter = 0;
		
}

//places the right image from ghost_sheet to game->ghosty
static void	set_ghost(t_game *game)
{
	size_t		dis_x;
	size_t		dis_y;

	dis_x = game->enemy->g_x - game->rays->p_x;
	dis_y = game->enemy->g_y - game->rays->p_y;

	// to find one picture from the whole map (432px * 432px)
	animate(game);
	game->enemy->ghosty = mlx_new_image(game->mlx, game->enemy->len, game->enemy->height);	
	if (!game->enemy->ghosty)
	{
		printf("No ghosty\n");
		return ;
	}
	game->enemy->distance = sqrt(dis_x * game->enemy->g_x + dis_y * game->enemy->g_y);
	game->enemy->angl_to_p = atan2(dis_y, dis_x);
	game->enemy->angl = game->enemy->angl_to_p - game->player_angl;

	draw_enemy(game, game->enemy->len, game->enemy->height);
}

static bool	init_enemy(t_game *game)
{
	if (!game->enemy)
	{
		game->enemy = malloc(sizeof(t_enemy));
		if(!game->enemy)
		{
			ft_printf("Allocation failed in ghostie\n");
			return (false);
		}
	}
	game->enemy->ghost_sheet = mlx_load_png(ENEMYP);
	if(!game->enemy->ghost_sheet)
	{
		ft_printf("No ghost\n");
		return (false);
	}
	colour_flip((uint32_t *)game->enemy->ghost_sheet->pixels, 
		game->enemy->ghost_sheet->width, game->enemy->ghost_sheet->height);
	return (true);
}

// Check that ghosty is not on the 1 or player

static bool	check_position(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 3;
	y = 2;
	game->enemy->g_x = x;
	game->enemy->g_y = y;

	if (x >= game->height || y >= game->longest)
	{
		printf("Enemy is out of bounds\n");
		return (false);
	}
	while (y < game->longest && game->map[x][y] != '\0' && 
			(game->map[x][y] == '1' || game->map[x][y] == 'W' ||
			game->map[x][y] == 'E'|| game->map[x][y] == 'S' ||
			game->map[x][y] == 'N' ))
	{
		y++;
		if (y >= game->longest || y >= ft_strlen(game->map[x]))
			return (false);
	}
	if (game->map[x][y] == '0' || game->map[x][y] == 'G')
	{
		game->map[x][y] = 'G';
		game->enemy->g_x = x;
		game->enemy->g_y = y;
		return (true);
	}
	else
		return (false);
}

// set's the ghost to the map (on the row 3)
void	ghostie(t_game *game)
{
	int screen_x;
	int size;
	
	if(!init_enemy(game))
		return ;
	if(!check_position(game))
		return ;
	set_ghost(game);
	screen_x = (game->enemy->angl / (FOW / 2)) * (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 2);
	size = TILE / game->enemy->distance;
	mlx_image_to_window(game->mlx, game->enemy->ghosty, screen_x, WINDOW_HEIGHT / 2 - size / 2);
}