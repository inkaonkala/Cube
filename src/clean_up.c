/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:58:39 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/22 18:22:50 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void clean_all_exit(t_game *game, char *message)
{
	if (game->file_content)
        free_grid(game->file_content);
    if (game->map)
        free_grid(game->map);
    if (game->no_texture_path)
        free(game->no_texture_path);
    if (game->so_texture_path)
        free(game->so_texture_path);
    if (game->ea_texture_path)
        free(game->ea_texture_path);
    if (game->we_texture_path)
        free(game->we_texture_path);
    if (game->floor_color)
        free(game->floor_color);
    if (game->ceiling_color)
        free(game->ceiling_color);
    if(game->c_split)
        free_grid(game->c_split);
    if(game->f_split)
        free_grid(game->f_split);
    if (message != NULL)
    {
		ft_putendl_fd("Error: ", 2);
        ft_putendl_fd(message, 2);
	} 
	exit(1);
}

void free_grid(char **grid)
{
    size_t i;

    i = 0;
    while (grid[i])
    {
        free(grid[i]);
        i++;
    }
    free(grid);
}