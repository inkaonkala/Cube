/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghostie_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:49:31 by iniska            #+#    #+#             */
/*   Updated: 2024/11/26 10:03:00 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	animate(t_game *game)
{
	static int	frame_counter = 0;
	static int	delay = 0;
	int			delay_f;

	delay_f = 9;
	game->g->height = game->g->ghost_sheet->height / 4;
	game->g->len = game->g->ghost_sheet->width / 4;
	if (delay >= delay_f)
	{
		game->g->row = frame_counter / 12;
		game->g->col = frame_counter % 12;
		frame_counter++;
		if (frame_counter >= 96)
			frame_counter = 0;
		delay = 0;
	}
	else
		delay++;
}

void	set_ghost(t_game *game)
{
	size_t		dis_x;
	size_t		dis_y;

	dis_x = game->g->g_x - game->rays->p_x;
	dis_y = game->g->g_y - game->rays->p_y;
	game->g->distance = sqrt(dis_x * dis_x + dis_y * dis_y);
	animate(game);
	game->g->ghosty = mlx_new_image(game->mlx, game->g->len, game->g->height);
	if (!game->g->ghosty)
	{
		ft_putendl_fd("No ghosty\n", 2);
		return ;
	}
	game->g->angl_to_p = atan2(dis_y, dis_x);
	game->g->angl = fmod(game->g->angl_to_p - game->player_angl
			+ PI, 2 * PI) - PI;
	game->g->pic = game->g->ghost_sheet;
	game->g->pixels = (uint32_t *)game->g->pic->pixels;
}

static bool	init_g(t_game *game)
{
	if (!game->g)
	{
		game->g = ft_calloc(sizeof(t_g), 1);
		if (!game->g)
		{
			ft_putendl_fd("Allocation failed in ghostie\n", 2);
			return (false);
		}
	}
	if (game->g->ghost_sheet)
		mlx_delete_texture(game->g->ghost_sheet);
	game->g->ghost_sheet = mlx_load_png(GP);
	if (!game->g->ghost_sheet)
	{
		ft_putendl_fd("No ghost\n", 2);
		return (false);
	}
	colour_flip((uint32_t *)game->g->ghost_sheet->pixels,
		game->g->ghost_sheet->width, game->g->ghost_sheet->height);
	return (true);
}

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
				game->g->g_x = y;
				game->g->g_y = x;
				return (true);
			}
			y++;
		}
		y = 0;
		x++;
	}
	ft_printf("Ghosty does not fit in here!\n");
	return (false);
}

void	ghostie(t_game *game)
{
	static int	flag = 0;

	if (flag < 2)
	{
		if (flag == 0)
		{
			flag = 1;
			if (!init_g(game))
				return ;
		}
		if (!check_position(game))
		{
			flag = 3;
			return ;
		}
		set_ghost(game);
	}
}
