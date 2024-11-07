
#include "../include/cub3D.h"

int check_texture_extension(t_game *game)
{
	int len;
	
	len = ft_strlen(game->ea_texture_path);
	if (len <= 4 || ft_strncmp(game->ea_texture_path + (len - 4), ".png", 4) != 0)
		return (0); 
	
	len = ft_strlen(game->so_texture_path);
	if (len <= 4 || ft_strncmp(game->so_texture_path + (len - 4), ".png", 4) != 0)
		return (0); 
	len = ft_strlen(game->we_texture_path);
	if (len <= 4 || ft_strncmp(game->we_texture_path + (len - 4), ".png", 4) != 0)
		return (0); 
	len = ft_strlen(game->no_texture_path);
	if (len <= 4 || ft_strncmp(game->no_texture_path + (len - 4), ".png", 4) != 0)
		return (0); 
	return (1); //filename with .png
}

int check_file_extesion(char *filename)
{
	int len;
	
	len = ft_strlen(filename);
	if (len <= 4 || ft_strncmp(filename + (len - 4), ".cub", 4) != 0)
	{
		//dprintf(2, "len\n");
		return (0); 
	}
	if (filename[len - 1] == '/')//file name with /
	{
		//dprintf(2, "len2\n");
		return (0); 
	}
	return (1); //filename with .cub
}

void check_player_position(t_game *game, char ** map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				game->player_x = j;
				game->player_y = i;
			}
			j++;
		}
		i++;
	}
}