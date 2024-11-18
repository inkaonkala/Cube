/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:02:51 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/18 18:51:07 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int check_empty_map(t_game *game)
{
	int i;

	i = game->last_item; 
	if (game->file_content[i + 1]== NULL)
		return (1);
	while(game->file_content[i])
	{
		if (empty_line(game->file_content[i]) == 1)
			return (2);
		i++;
	}

	return (0);
}

static int check_empty_line(t_game *game, char *mapfile)
{
	int fd;
	char *new_line;
	int empty;
	int j;

	j = 0;
	empty = 0;
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		return (1);
	new_line = get_next_line(fd);
	//dprintf(2, "game->last_item: %d\n",game->last_item);
	while(j < game->last_item + 2 || new_line[0] == '\n' || new_line == NULL)//
	{
		free(new_line);
		new_line = get_next_line(fd);
		j++;
	}		
	//dprintf(2, "line: %s,j: %d\n", new_line, j);
	while (new_line)
	{
		if (new_line && empty == 1)
			return (1);
		if ((new_line == NULL || new_line[0] == '\n' ) && empty == 0)
			empty = 1;
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (0);
}



static int parse_element(t_game *game, t_flag *flags, char *mapfile)
//static int parse_element(t_game *game, char *mapfile)
{
	//check walls f  info 確認牆天地資訊有沒有齊
	if (check_elements_info(game, game->file_content, flags) == 1)
	{    
		free(game->flags);
		clean_all_exit(game, "invalid Elementssss");
	} // return 1 means wrong
	free(game->flags);	
	
	if (check_texture_extension(game) == 0)
		clean_all_exit(game, "please provide a '.png' texture");
	
	save_colors(game, game->file_content);
	//check color 
	set_color(game); 
	//check empty map
	if (check_empty_map(game) == 1)
		clean_all_exit(game, "The map is EMPTY!");
	else if (check_empty_map(game) == 2)
		clean_all_exit(game, "Tha map has an empty line.");
	//check empty line
	if (check_empty_line(game, mapfile) == 1)
		clean_all_exit(game, "Tha map has empty line(s).");
	
	
	if (create_map(game, game->file_content + (game->last_item + 1))== 1)
		clean_all_exit(game, "The map's memory allocation failed"); // map didn allocate correctly
	
	return (0);
}

static void parse_file(t_game *game, char *mapfile)
{
	
	game->flags = ft_calloc(1, sizeof(t_flag));
	if (game->flags == NULL)
		clean_all_exit(game, "malloc failed");
	
	game->file_content = get_2d_array(mapfile);
	
	if (game->file_content == NULL)
	{
		free(game->flags);
		clean_all_exit(game, "Cannot read the mapfile!");
	}
		
	if (game->file_content[0] == NULL)
		clean_all_exit(game, "The file is empty!");
	
	
	

	
	//parse_element(game, mapfile);
	parse_element(game, game->flags, mapfile);		

	//free_grid(game->file_content);
	//game->file_content = NULL;

}

void init_game(t_game *game, char *mapfile)
{
	game->death = false;
	game->win = false;
	parse_file(game, mapfile);
	

	// dprintf(2, "game->no_texture_path: %s\n", game->no_texture_path);
	// dprintf(2, "game->ea_texture_path: %s\n", game->ea_texture_path);
	// dprintf(2, "game->so_texture_path: %s\n", game->so_texture_path);
	// dprintf(2, "game->we_texture_path: %s\n", game->we_texture_path);
	
	//check map
	
	// int l = 0;
	// while (game->map[l])
	// {
	// 	dprintf(2, "game->map[%d]: %s\n",l, game->map[l]);
	// 	l++;
	// }

	map_validate(game);	

	
	//create ractagle map
	create_rectagle(game);//create rectangle amd fill space with 1
	//get position 
	
	
	check_player_position(game, game->map);

	// dprintf(2, "player position: x:%zu y: %zu\n", game->player_x, game->player_y);
	
	//  l = 0;
	// while (game->map[l])
	// {
	// 	dprintf(2, "game->map[%d]: %s\n",l, game->map[l]);
	// 	l++;
	// }


	// dprintf(2, "game->ceiling_color: %s\n", game->ceiling_color);
	// dprintf(2, "game->floor_color: %s\n", game->floor_color);

	// dprintf(2, "game->floor_r: %d\n", game->floor_r);
	// dprintf(2, "game->floor_g: %d\n", game->floor_g);
	// dprintf(2, "game->floor_b: %d\n", game->floor_b);
	// dprintf(2, "game->ceiling_r: %d\n", game->ceiling_r);
	// dprintf(2, "game->ceiling_g: %d\n", game->ceiling_g);
	// dprintf(2, "game->ceiling_b: %d\n", game->ceiling_b);

	

}






