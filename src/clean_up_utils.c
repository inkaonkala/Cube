/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:24:36 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/21 14:02:05 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_grid(char **grid)
{	
	size_t	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		if (grid[i])
		{
			free(grid[i]);
			grid[i] = NULL;
		}
		i++;
	}
	free(grid);
	grid = NULL;
}	

void	free_texture(t_game *game)
{
	if (game->no_texture_path)
		free(game->no_texture_path);
	if (game->so_texture_path)
		free(game->so_texture_path);
	if (game->ea_texture_path)
		free(game->ea_texture_path);
	if (game->we_texture_path)
		free(game->we_texture_path);
	if (game->no_texture)
		mlx_delete_texture(game->no_texture);
	if (game->so_texture)
		mlx_delete_texture(game->so_texture);
	if (game->we_texture)
		mlx_delete_texture(game->we_texture);
	if (game->ea_texture)
		mlx_delete_texture(game->ea_texture);
}

void	delete_image(t_game *game)
{	
	if (game->door)
	{
		mlx_delete_image(game->mlx, game->door);
	}
	if (game->mini_player)
	{
		mlx_delete_image(game->mlx, game->mini_player);
	}
	if (game->minimap)
	{
		mlx_delete_image(game->mlx, game->minimap);
	}
}
