/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:02:51 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/18 15:47:29 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int check_file_extesion(char *filename)
{
	int len;
	
	len = ft_strlen(filename);
	if (len <= 4 || ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
	{
		dprintf(2, "len\n");
		return (0); 
	}
	if (filename[len - 1] == '/')//file name with /
	{
		dprintf(2, "len2\n");
		return (0); 
	}
	return (1); //filename with .cub
}

char *readfile(char *mapfile)
{

	char *new_line;
	char *map_str;
	//char *temp;
	int		fd;
	
	fd = open(mapfile, O_RDONLY); 
	if (fd == -1)
		return (NULL);
	
	map_str = ft_calloc(1, 1);//inistialize map str ito avoid carbage value
	if (map_str == NULL)
		return NULL;
	new_line = get_next_line(fd);
	while (new_line)
	{
		//temp = new_line;
		map_str = ft_strjoin(map_str, new_line);
		//free(temp);
		free(new_line);
		new_line = get_next_line(fd);
	}
	
	close (fd);
	return (map_str);
}


char **get_2d_array( char *mapfile)
{
	char	*file_str;
	char	**result;
	
	file_str = readfile(mapfile);
	if (file_str == NULL)
	{
		perror("Cannot read the map!");
		return (NULL);
	}
	result = ft_split(file_str, '\n');
	free(file_str);
	if (result == NULL)
	{
		perror(" Spit failed.");
		return (NULL);
	}
	return (result);
}

int parse_element(t_game *game, char *mapfile)
{
	//check map info 

	//parse map info (make map regtangular)

	//check color 
	//set color 
}

void parse_file(t_game *game, char *mapfile)
{
	game->file_content = get_2d_array( mapfile);
	if (game->file_content == NULL)
		clean_all_exit(game, "Cannot read the mapfile!");
	if (game->file_content[0] == NULL)
		clean_all_exit(game, "The file is empty!");

	parse_element(game, mapfile);
	clean_grid(game, );
	game->file_content = NULL;
	
}
	

void init_game(t_game *game, char *mapfile)
{
	
	//parse file : create sd array map,  parse element
	
	parse_file(game, mapfile);
	
	
	
	//test
	int i = 0;
	while (game->file_content[i])
	{
		dprintf(2,"game->file_content:  %s\n", game->file_content[i]) ;
		
		i++;
	}
	
	//map validation: check map size too big too small, empty , invalid char, has NSEW once, if map is closed
	
	//get position 
}





