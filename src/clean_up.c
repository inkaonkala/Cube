/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:58:39 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/19 14:45:22 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void free_texture(t_game *game)
{
	
	 if (game->no_texture_path)
        free(game->no_texture_path);
    if (game->so_texture_path)
        free(game->so_texture_path);
    if (game->ea_texture_path)
        free(game->ea_texture_path);
    if (game->we_texture_path)
	{
		
        free(game->we_texture_path);
	}
	
	if (game->no_texture)
		mlx_delete_texture(game->no_texture);
	if (game->so_texture)
		mlx_delete_texture(game->so_texture);
	if (game->we_texture)
		mlx_delete_texture(game->we_texture);
	if (game->ea_texture)
		mlx_delete_texture(game->ea_texture);
	
	if (game->g->ghost_sheet)
	{
		mlx_delete_texture(game->g->ghost_sheet);
	}
	//if (game->enemy->pic)
		//mlx_delete_texture(game->enemy->pic);
     // door bonus
    if (game->door_close_texture)
        mlx_delete_texture(game->door_close_texture);
    if (game->door_open_texture)
        mlx_delete_texture(game->door_open_texture);
}


void delete_image(t_game *game)
{
	if (game->gameover_image)
	{
		
        mlx_delete_image(game->mlx, game->gameover_image);
	}
	
	
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
	   
	if (game->canvas)
	{
		mlx_delete_image(game->mlx, game->canvas);
	}
}


void clean_all(t_game *game)
{
	if (game->file_content)
        free_grid(game->file_content);
		
	
    if (game->map)
	{
		free_grid(game->map);
	}
	
	
	free_texture(game);
	
	if (game->floor_color)
        free(game->floor_color);
		
	

    if (game->ceiling_color)
	{
		
        free(game->ceiling_color);
	}
		
	
    if (game->c_split)
	{
		
        free_grid(game->c_split);
	}
		
	
    if (game->f_split)
	{
    	free_grid(game->f_split);
	}
	
		
	delete_image(game);
    
	if (game->rays)
		free(game->rays);

	if (game->g)
		free(game->g);
	if (game->mlx)
		mlx_terminate(game->mlx);
		
	if (game != NULL)
		free(game);
}


void clean_all_exit(t_game *game, char *message)
{
	if (game->file_content)
	{
        free_grid(game->file_content);
	}
    if (game->map)
	{
        free_grid(game->map);
	}
	free_texture(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
		
    if (game->floor_color)
        free(game->floor_color);
    if (game->ceiling_color)
        free(game->ceiling_color);
		
    if (game->c_split)
	{
        free_grid(game->c_split);
	}
	
    if (game->f_split)
	{
        free_grid(game->f_split);
	}
	if (game->gameover_image)
        mlx_delete_image(game->mlx, game->gameover_image);
    if (game->door)
	{
        mlx_delete_image(game->mlx, game->door);
	}
	if (game->canvas)
		mlx_delete_image(game->mlx, game->canvas);
		
	if (game != NULL)
		free(game);
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

    if (!grid)
        return;

    i = 0;
    while (grid[i])
    {
        if (grid[i])  // 檢查 grid[i] 是否有效
        {
            free(grid[i]);
            grid[i] = NULL;  // 防止重複釋放
        }
        i++;
    }
    free(grid);
    grid = NULL;
}
