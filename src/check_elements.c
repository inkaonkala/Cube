
#include "../include/cub3D.h"

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
}


int check_elements_info(t_game *game,char **file_content, t_flag *flags)//return 1代表錯誤
{
	int last; // last element
	
	init_flags(flags);

	flags->game = game;//init flags->game point to t_game

	last = check_all_elements(file_content, game->flags);
	
	if (last == -1 || flags->all_flags != 6 )
		return (1);	
	
	check_duplicate(file_content, game->flags, last);
	
	if (flags->duplicate == 1)
	{
		return (1);
	}
		
	game->last_item = last - 1;
	return (0);
}