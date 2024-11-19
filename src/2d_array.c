#include "../include/cub3D.h"

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
	result = ft_split( file_str, '\n');
	free(file_str);
	if (result == NULL)
	{
		perror("Spit failed.");
		return (NULL);
	}
	return (result);
}