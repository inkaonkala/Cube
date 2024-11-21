/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:58:39 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/21 16:58:28 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	free_bonus_texture(t_game *game)
{
	if (game->g->ghost_sheet)
	{
		mlx_delete_texture(game->g->ghost_sheet);
	}
	if (game->door_close_texture)
	{
		mlx_delete_texture(game->door_close_texture);
	}
	if (game->door_open_texture)
	{
		mlx_delete_texture(game->door_open_texture);
	}
}

static void	clean_all_2(t_game *game)
{
	if (game->c_split)
		free_grid(game->c_split);
	if (game->f_split)
		free_grid(game->f_split);
	if (game->gameover_image)
		mlx_delete_image(game->mlx, game->gameover_image);
	if (BONUS > 0)
		delete_image(game);
	if (game->gameover_image)
		mlx_delete_image(game->mlx, game->gameover_image);
	if (game->canvas)
		mlx_delete_image(game->mlx, game->canvas);
	if (game->rays)
		free(game->rays);
	if (BONUS > 0)
		if (game->g)
			free(game->g);
}

void	clean_all(t_game *game)
{
	if (game->file_content)
		free_grid(game->file_content);
	if (game->map)
		free_grid(game->map);
	free_texture(game);
	if (BONUS > 0)
		free_bonus_texture(game);
	if (game->floor_color)
		free(game->floor_color);
	if (game->ceiling_color)
		free(game->ceiling_color);
	clean_all_2(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game != NULL)
		free(game);
}

void	clean_all_exit(t_game *game, char *message)
{
	if (game->file_content)
		free_grid(game->file_content);
	if (game->map)
		free_grid(game->map);
	free_texture(game);
	if (BONUS > 0)
		free_bonus_texture(game);
	if (game->floor_color)
		free(game->floor_color);
	if (game->ceiling_color)
		free(game->ceiling_color);
	clean_all_2(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game != NULL)
		free(game);
	if (message != NULL)
	{
		ft_putendl_fd("Error: ", 2);
		ft_putendl_fd(message, 2);
	}
	exit(1);
}
