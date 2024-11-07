/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghostie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:49:31 by iniska            #+#    #+#             */
/*   Updated: 2024/11/05 13:43:10 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static	void	draw_enemy(t_game *game, int frame_w, int frame_l)
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

//places the right image from ghost_sheet to game->ghosty
static void	set_ghost(t_game *game)
{

	// to find one picture from the whole map (432px * 432px)
	game->enemy->height = 432 / 8;
	game->enemy->len = 432 / 12;
	game->enemy->ghosty = mlx_new_image(game->mlx, game->enemy->len, game->enemy->height);	
	if (!game->enemy->ghosty)
	{
		printf("No ghosty\n");
		return ;
	}
	draw_enemy(game, game->enemy->len, game->enemy->height);
}

static void	init_enemy(t_game *game)
{
	if (!game->enemy)
	{
		game->enemy = malloc(sizeof(t_enemy));
		if(!game->enemy)
		{
			ft_printf("Allocation failed in ghostie\n");
			return ;
		}
	}
}

// set's the ghost to the map (on the row 3)
void	ghostie(t_game *game)
{
	int x;
	int	y;

	x = 3;
	y = 2;
	init_enemy(game);
	
	game->enemy->ghost_sheet = mlx_load_png(ENEMYP);
	if(!game->enemy->ghost_sheet)
	{
		ft_printf("No ghost\n");
		return ;
	}
	if (game->longest > 5 && game->height > 4)
	{
		while (game->map[x][y] && (game->map[x][y] == '1' || game->map[x][y] == 'W'
				|| game->map[x][y] == 'E'|| game->map[x][y] == 'S'
				|| game->map[x][y] == 'N' )) //and the line is not at the end! && game->map[x][y] != '\0' this segfaults)
		{
			y++;
		}
		if(game->map[x][y] == '0')
		{
			printf("enemy cords: %d, %d\n", x, y);
			game->enemy->g_x = x;
			game->enemy->g_y = y;
			game->enemy->row = x;
			game->enemy->col = y;
			set_ghost(game);
		}
	}
	mlx_image_to_window(game->mlx, game->enemy->ghosty, game->enemy->g_x * TILE, game->enemy->g_y * TILE);
}