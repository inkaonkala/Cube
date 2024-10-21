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

void init_flags(t_flag *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->f = 0;
	flags->c = 0;
	flags->duplicate = 0;;
	flags->all_flags = 0;
	flags->game = NULL;
}

int empty_line(char * file)
{	
	int i;
	
	i = 0;
	while(file[i] != '\0')
	{
		
		if (file[i] != ' ' && file[i] != '\t')
		{
			
			return (0);
		}	
		i++;
	}
	
	return (1);
}
////////////有 texture
int set_flag(char *file_line, t_flag *flags, int *flag, char **texture_path)
{
	
	if (*flag == 1)
	{
		flags->duplicate = 1;
		return (1);
	}
	
	*flag = 1;
	flags->all_flags++;
	
	if (file_line != NULL)
		*texture_path = (file_line + 3);
	//dprintf(2, "in flag file_line:%s  \n",file_line);
	//dprintf(2, "in flag texture_path:%s  \n",*texture_path);
	return (0);
}


int set_flags(char *file_line, t_flag *flags)// 1 already has the info,  0 new 
{
	if (*file_line == ' ' || *file_line == '\t')
		file_line++;
	if (ft_strncmp(file_line, "NO ", 3) == 0)
	{
		return (set_flag(file_line, flags, &flags->no, &flags->game->no_texture_path));
	}
	if (ft_strncmp(file_line, "WE ", 3) == 0)
	{
		return (set_flag(file_line, flags, &flags->we, &flags->game->we_texture_path));
	}	
	if (ft_strncmp(file_line, "SO ", 3) == 0)
		return (set_flag(file_line, flags, &flags->so, &flags->game->so_texture_path));
	if (ft_strncmp(file_line, "EA ", 3) == 0)
		return (set_flag(file_line, flags, &flags->ea, &flags->game->ea_texture_path));
	if (ft_strncmp(file_line, "F ", 2) == 0)
	{
		return (set_flag(file_line, flags, &flags->f, &flags->game->floor_color));
	}	
	if (ft_strncmp(file_line, "C ", 2) == 0)
		return (set_flag(file_line, flags, &flags->c, &flags->game->ceiling_color));
	return (0);
}


int check_all_elements(char **file, t_flag *flags)
{
	int i;
	int count;

	i = 0;
	count = 0; 
	
	while(file[i] && count < 6)
	{
		
		if (empty_line(file[i]) == 1)
		{
			i++;
			continue;
		}
		else if (set_flags(file[i], flags) == 1)
		{
			
			return (-1);
		}
		//else if (set_flags(file[i], flags) == 0) // 有6個flags
		else
		{
			//dprintf(2, "file[i]: %s\n",file[i]);
			i++;
			count++;
		}
	
	}
	
	return (i);// i = last item
}

void check_duplicate(char **file, t_flag *flags, int last_item)
{
	
	while(file[last_item])
	{
		if (empty_line(file[last_item]) == 1)
		{
			last_item++;
			continue;
		}
		set_flags(file[last_item], flags);
		last_item++;
	}
}


int check_elements_info(t_game *game,char **file_content, t_flag *flags)//return 1代表錯誤
{
	int last; // last element
	
	init_flags(flags);

	flags->game = game;//init flags->game point to t_game

	last = check_all_elements(file_content, game->flags);
	
	if (last == -1 || flags->all_flags != 6 )
		return (1);	
	
	//check_duplicate(file_content, game->flags, last);  待處理  這是錯的
	
	if (flags->duplicate == 1)
	{
		dprintf(2, "duplicate\n");
		return (1);
	}
		
	game->last_item = last - 1;
		
	return (0);
}

//int save_colors(t_game *game, char **file_content, t_flag *flags)
int save_colors(t_game *game, char **file_content)
{
	int i;
	int j;

	i = 0;
	while(file_content[i])
	{
		if (empty_line(file_content[i]) == 1)
		{
			i++;
			continue;
		}
		j = 0;
		while(file_content[i][j])
		{
			if (file_content[i][j] == ' ' || file_content[i][j] == '\t')
				j++;
			if (ft_strncmp(file_content[i] + j, "F ", 2) == 0)
				game->ceiling_color = file_content[i] + j + 2;
			else if (ft_strncmp(file_content[i] + j, "C ", 2) == 0)
				game->floor_color = file_content[i] + j + 2;
			j++;	
		}
		i++;
	}
	return (0);
}

int count_char(char *color, char a)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (color[i])
	{
		if (color[i] == ',')
			j++;
		i++;
	}
	retunr (j);
}


void set_color(t_game *game)
{
	if (count_char(game->ceiling_color, ',')  != 2 || count_char(game->floor_color, ',')  != 2)// ,
		clean_all_exit(game, "wrong color fomat");
	//split 
	//check three numbers amd all digits 
	// save them to struct f_r f_g f_b
	

	free_grid(game->c_split);
	free_grid(game->f_split);
	game->f_split = NULL;
	game->c_split = NULL;
}

//int parse_element(t_game *game, char *mapfile, t_flag *flags)
int parse_element(t_game *game, t_flag *flags)
{
	dprintf(2, "in parse_element\n");
	//check walls f  info 確認牆天地資訊有沒有齊
	if (check_elements_info(game, game->file_content, flags) == 1)
	{    
	
		free(game->flags);
		free(game->flags->game);
		clean_all_exit(game, "unvalid elements");
	} // return 1 代表錯誤
	free(game->flags);
	
	//parse walls f  info
	//set_color(game, game->file_content, flags);
	dprintf(2, "game->no_texture_path: %s\n", game->no_texture_path);
	dprintf(2, "game->ea_texture_path: %s\n", game->ea_texture_path);
	dprintf(2, "game->so_texture_path: %s\n", game->so_texture_path);
	dprintf(2, "game->we_texture_path: %s\n", game->we_texture_path);
	
	save_colors(game, game->file_content);
	dprintf(2, "game->ceiling_color: %s\n", game->ceiling_color);
	dprintf(2, "game->floor_color: %s\n", game->floor_color);
	//check color 
	set_color(game); 

	//check empty map
	//check empty line
	//create map

	/////inka can test RACAST
	return (0);
}

void parse_file(t_game *game, char *mapfile)
{
	
	game->flags = ft_calloc(1, sizeof(t_flag));
	if (game->flags == NULL)
		clean_all_exit(game, "malloc failed");
	
	
	
	game->file_content = get_2d_array( mapfile);
	
	if (game->file_content == NULL)
		clean_all_exit(game, "Cannot read the mapfile!");


	if (game->file_content[0] == NULL)
		clean_all_exit(game, "The file is empty!");
	
	//parse_element(game, mapfile, game->flags);
	parse_element(game, game->flags);

	free_grid(game->file_content);
	game->file_content = NULL;
	
}
	

void init_game(t_game *game, char *mapfile)
{
	
	//可能需要init game struct 因為行數過多
	//parse file : create sd array map,  parse element

	parse_file(game, mapfile);

	
	
	//map validation: check map size too big too small, empty , invalid char, has NSEW once, if map is closed
	//create ractagle map
	//get position 
}





