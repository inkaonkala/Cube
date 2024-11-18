/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:43:42 by iniska            #+#    #+#             */
/*   Updated: 2024/11/18 12:58:23 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void winning_image(t_game *game)
{
	mlx_texture_t	*pic;
	mlx_image_t		*pixels;
	int				offsex;
	int				offsey;

	pic = mlx_load_png(WINIMA);
	if(!pic)
		return ;
	offsex = (WINDOW_WIDTH - pic->width) / 2;
	offsey = (WINDOW_HEIGHT - pic->height) / 2;
	pixels = mlx_texture_to_image(game->mlx, pic);
	if (!pixels)
	{
		mlx_delete_texture(pic);
		return ;
	}
	mlx_image_to_window(game->mlx, pixels, offsex, offsey);
	mlx_delete_texture(pic);
}	

void	game_over_image(t_game *game)
{
	mlx_texture_t	*pic;
	mlx_image_t		*pixels;
	int				offsex;
	int				offsey;

	pic = mlx_load_png(GAMEOVERI);
	if(!pic)
		return ;
	offsex = (WINDOW_WIDTH - pic->width) / 2;
	offsey = (WINDOW_HEIGHT - pic->height) / 2;
	pixels = mlx_texture_to_image(game->mlx, pic);
	if (!pixels)
	{
		mlx_delete_texture(pic);
		return ;
	}
	mlx_image_to_window(game->mlx, pixels, offsex, offsey);
	mlx_delete_texture(pic);
}


