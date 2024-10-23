/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:02:51 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/23 14:15:21 by iniska           ###   ########.fr       */
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

static char *readfile(char *mapfile)
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
	//dprintf(2, "newline:%s", new_line);
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


static char **get_2d_array( char *mapfile)
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


static char **twod_array( char *mapfile)
{
	char	*file_str;
	char	**result;
	
	file_str = readfile(mapfile);
	if (file_str == NULL)
	{
		perror("Cannot read the map!");
		return (NULL);
	}
	result = split_newline(file_str, '\n');
	free(file_str);
	if (result == NULL)
	{
		perror(" Spit failed.");
		return (NULL);
	}
	return (result);
}

static void init_flags(t_flag *flags)
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

static int empty_line(char * file)
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
static int set_flag(char *file_line, t_flag *flags, int *flag, char **texture_path)
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


static int set_flags(char *file_line, t_flag *flags)// 1 already has the info,  0 new 
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


static int check_all_elements(char **file, t_flag *flags)
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

static void check_duplicate(char **file, t_flag *flags, int last_item)
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
	dprintf(2, "flags->duplicate: %d\n",flags->duplicate );
}


static int check_elements_info(t_game *game,char **file_content, t_flag *flags)//return 1代表錯誤
{
	int last; // last element
	
	init_flags(flags);

	flags->game = game;//init flags->game point to t_game

	last = check_all_elements(file_content, game->flags);
	
	if (last == -1 || flags->all_flags != 6 )
		return (1);	
	
	check_duplicate(file_content, game->flags, last); // 待處理  這是錯的
	
	if (flags->duplicate == 1)
	{
		dprintf(2, "duplicate\n");
		return (1);
	}
		
	game->last_item = last - 1;
	
	return (0);
}

//int save_colors(t_game *game, char **file_content, t_flag *flags)
static int save_colors(t_game *game, char **file_content)
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
			if (ft_strncmp(file_content[i] + j, "C ", 2) == 0)
				game->ceiling_color = file_content[i] + j + 2;
			else if (ft_strncmp(file_content[i] + j, "F ", 2) == 0)
				game->floor_color = file_content[i] + j + 2;
			j++;	
		}
		i++;
	}
	return (0);
}

static int count_char(char *color, char a)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (color[i])
	{
		if (color[i] == a)
			j++;
		i++;
	}
	return (j);
}

static int check_rgb_digit(t_game *game, char c)
{
	int i;
	int j;
	char **array;
	i = 0;	
	if (c == 'f')
		array = game->f_split;
	else
		array = game->c_split;
	while (i < 3)
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] < 48 || array[i][j] > 57)
				return (1);
			j++;	
		}
		i++;
	}
	return (0);
}

static int  check_rgb_range(t_game *game)
{
	if (game->floor_r > 255 || game->floor_r < 0)
		return (-1);
	if (game->floor_g > 255 || game->floor_g < 0)
		return (-1);
	if (game->floor_b > 255 || game->floor_b < 0)
		return (-1);
	if (game->ceiling_r > 255 || game->ceiling_r < 0)
		return (-1);
	if (game->ceiling_g > 255 || game->ceiling_g < 0)
		return (-1);
	if (game->ceiling_b > 255 || game->ceiling_b < 0)
		return (-1);
	return (0);
}


static void find_color(char **c_split, char **f_split, t_game *game)
{
	int i;

	i = 0;
	while (c_split[i])
	{
		if (i == 0)
			game->ceiling_r = ft_atoi(c_split[i]);
		if (i == 1)
			game->ceiling_g = ft_atoi(c_split[i]);
		if (i == 2)
			game->ceiling_b = ft_atoi(c_split[i]);
		i++;
	}
	i = 0;
	while (f_split[i])
	{
		if (i == 0)
			game->floor_r = ft_atoi(f_split[i]);
		if (i == 1)
			game->floor_g = ft_atoi(f_split[i]);
		if (i == 2)
			game->floor_b = ft_atoi(f_split[i]);
		i++;
	}

	if (check_rgb_range(game) == -1)
		clean_all_exit(game, "available color range is 0 to 255");
}

static void set_color(t_game *game)
{
	if (count_char(game->ceiling_color, ',')  != 2 || count_char(game->floor_color, ',')  != 2)// ,
		clean_all_exit(game, "wrong color fomat, not with two ,");
	//split 
	game->c_split = ft_split(game->ceiling_color, ',');
	if (!game->c_split)
		clean_all_exit(game, "c_split split failed.");
	game->f_split = ft_split(game->floor_color, ',');
	if (!game->f_split)
		clean_all_exit(game, "f_split split failed.");
	if ( check_rgb_digit(game, 'f') == 1)//check three numbers and all digits
		clean_all_exit(game, "floor color format must be digit");
	if ( check_rgb_digit(game, 'c') == 1)//check three numbers and all digits
		clean_all_exit(game, "ceiling color format must be digit");

	dprintf(2, "before find color\n");
	// save them to struct f_r f_g f_b
	find_color(game->c_split, game->f_split, game);
	
	free_grid(game->c_split);
	free_grid(game->f_split);
	game->f_split = NULL;
	game->c_split = NULL;
}

static int check_empty_map(t_game *game)
{
	int i;

	i = game->last_item; 
	if (game->file_content[i + 1]== NULL)
		return (1);
	while(game->file_content[i])
	{
		if (empty_line(game->file_content[i]) == 1)
			return (1);
		i++;
	}

	return (0);
}


// int create_map(t_game *game)
// {
// 	int i;
// 	int j;
	
// 	game->map = ft_calloc(1, sizeof(char **));
	
// 	game->map = ft_calloc(100, sizeof(char *)); 
	
// 	j = 0;
// 	i = game->last_item + 1;
// 	while (game->file_content[i][0] == '\n' || empty_line(game->file_content[i]) == 1)
// 			i++;
// 	while (game->file_content[i] && game->file_content[i][0] != 'N' && game->file_content[i][0] != 'W' 
// 		&& game->file_content[i][0] != 'S' && game->file_content[i][0] != 'E' 
// 		&& game->file_content[i][0] != 'C'&& game->file_content[i][0] != 'F')
// 	{
// 		if (game->file_content_newline[i][0] == '\n' || empty_line(game->file_content_newline[i]) == 1)
// 			clean_all_exit(game, "the map is not valid");
// 		game->map[j] = game->file_content_newline[i];
// 		i++;
// 		j++;
// 	}
	
// 	game->map[j] = NULL;
// 	return (0);
// }

static int	count_2darray_size(char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
		i++;
	return (i);
}

static int	copy_string(char **copy, char *src, int i)
{
	int	j;

	copy[i] = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!copy[i])
		return (0);
	j = 0;
	while (src[j] != '\0')
	{
		copy[i][j] = src[j];
		j++;
	}
	copy[i][j] = '\0';
	return (1);
}

static char	**copy_2darray(char **src)
{
	char	**copy;
	int		size;
	int		i;

	i = 0;
	size = count_2darray_size(src);
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	while (src[i] != NULL)
	{
		if (!copy_string(copy, src[i], i))
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static char	**create_map(char **file_copy)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = copy_2darray(file_copy);
	if (!map)
		return (NULL);
	while (file_copy[i] != NULL)
	{
		j = 0;
		while (file_copy[i][j] != '\0')
		{
			if (file_copy[i][j] == ' ' || file_copy[i][j] == '\t')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (map);
}


//int parse_element(t_game *game, char *mapfile, t_flag *flags)
static int parse_element(t_game *game, t_flag *flags)
{
	
	//check walls f  info 確認牆天地資訊有沒有齊
	if (check_elements_info(game, game->file_content, flags) == 1)
	{    
	
		free(game->flags);
		clean_all_exit(game, "unvalid elements");
	} // return 1 代表錯誤
	free(game->flags);
	
	//parse walls f  info
	//set_color(game, game->file_content, flags);
	// dprintf(2, "game->no_texture_path: %s\n", game->no_texture_path);
	// dprintf(2, "game->ea_texture_path: %s\n", game->ea_texture_path);
	// dprintf(2, "game->so_texture_path: %s\n", game->so_texture_path);
	// dprintf(2, "game->we_texture_path: %s\n", game->we_texture_path);
	
	save_colors(game, game->file_content);
	
	// dprintf(2, "game->ceiling_color: %s\n", game->ceiling_color);
	// dprintf(2, "game->floor_color: %s\n", game->floor_color);

	
	//check color 
	set_color(game); 
	
	// dprintf(2, "game->floor_r: %d\n", game->floor_r);
	// dprintf(2, "game->floor_g: %d\n", game->floor_g);
	// dprintf(2, "game->floor_b: %d\n", game->floor_b);
	// dprintf(2, "game->ceiling_r: %d\n", game->ceiling_r);
	// dprintf(2, "game->ceiling_g: %d\n", game->ceiling_g);
	// dprintf(2, "game->ceiling_b: %d\n", game->ceiling_b);

	
	//check empty map
	if (check_empty_map(game) ==1)
		clean_all_exit(game, "The map is EMPTY!");
	//check empty line
	
	
	//create_map(game);
	game->map = create_map(game->file_content+(game->last_item + 1));

	int l = 0;

	while (game->map[l])
	{
		dprintf(2, "game->map[%d]: %s\n",l, game->map[l]);
		l++;
	}

	
	/////inka can test RACAST
	return (0);
}

static void parse_file(t_game *game, char *mapfile)
{
	
	game->flags = ft_calloc(1, sizeof(t_flag));
	if (game->flags == NULL)
		clean_all_exit(game, "malloc failed");
	
	game->file_content = get_2d_array(mapfile);
	game->file_content_newline = twod_array(mapfile);
	
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






