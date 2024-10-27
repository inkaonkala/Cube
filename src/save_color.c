

#include "../include/cub3D.h"


static int set_t_path(char **map_t_path, char * t_path)
{
	//if (*map_t_path)
		//free(*map_t_path);
	*map_t_path = ft_strtrim(t_path, " ");
	if (!*map_t_path)
	{
		err_message("ft_strtrim() failed in set_t_path");
		return (1);
	}
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
			if (ft_strncmp(file_content[i] + j, "C ", 2) == 0)
			{
				if (set_t_path(&game->ceiling_color, file_content[i] + j + 2) == 1)
					return (1);
				//game->ceiling_color = file_content[i] + j + 2;
			}
			else if (ft_strncmp(file_content[i] + j, "F ", 2) == 0)
			{
				if (set_t_path(&game->floor_color, file_content[i] + j + 2) == 1)
					return (1);
				//game->floor_color = file_content[i] + j + 2;
			}
				
			j++;	
		}
		i++;
	}
	return (0);
}