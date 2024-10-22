/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:58:39 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/22 18:35:18 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void clean_all_exit(t_game *game, char *message)
{
	// if (game->file_content)
    //     free_grid(game->file_content);
    // if (game->map)
    //     free_grid(game->map);
    //need to add more paramerters in struct
	ft_putendl_fd("not important error info need to delete", 2);
	ft_putendl_fd(game->ceiling_color, 2);

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
