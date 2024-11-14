/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghostie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:49:31 by iniska            #+#    #+#             */
/*   Updated: 2024/11/14 15:19:20 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	animate(t_game *game)
{
	static int	frame_counter = 0;
	static int	delay = 0;
	int			delay_f;

	delay_f = 7;
	game->enemy->height = 423 / 8; // or 53
	game->enemy->len = 432 / 12;

	if (delay >= delay_f)
	{
		game->enemy->row = frame_counter / 12;
		game->enemy->col = frame_counter % 12;
		frame_counter++;
		if(frame_counter >= 96)
			frame_counter = 0;
		delay = 0;
	}
	else
		delay++;
}


/*
void	animate(t_game *game)
{
	static int	frame_counter = 0;

	game->enemy->height = 423 / 8;
	game->enemy->len = 432 / 12;

	game->enemy->row = frame_counter / 12;
	game->enemy->col = frame_counter % 12;
	frame_counter++;
	if(frame_counter >= 96)
		frame_counter = 0;

}
*/

//places the right image from ghost_sheet to game->ghosty
void	set_ghost(t_game *game)
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
	game->enemy->distance = sqrt(dis_x * dis_x + dis_y * dis_y);
	game->enemy->angl_to_p = atan2(dis_y, dis_x);
	game->enemy->angl = fmod(game->enemy->angl_to_p - game->player_angl + PI, 2 * PI) - PI;

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

	x = 2;
	y = 3;
	while (x < game->height)
	{
		while (y < game->longest && y < ft_strlen(game->map[x]))
		{
			if (game->map[x][y] == '0' || game->map[x][y] == 'G')
			{
				game->map[x][y] = 'G';
				game->enemy->g_x = x;
				game->enemy->g_y = y;
				return (true);
			}
			y++;
		}
		y = 0;
		x++;
	}
	ft_printf("Enemy does not fit in here!\n");
	return (false);
}

/*
static bool	check_position(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 2;
	y = 3;
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
}*/

// set's the ghost to the map (on the row 2)
void	ghostie(t_game *game)
{
	//int screen_x;
	//int size;
	
	if(!init_enemy(game))
		return ;
	if(!check_position(game))
		return ;
	set_ghost(game);
	//screen_x = (game->enemy->angl / (FOW / 2)) * (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 2);
	//size = game->enemy->distance; // CHECK THE SIZE HERE!!!
}