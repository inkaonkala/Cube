/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:59:46 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/21 15:07:03 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_empty_map(t_game *game)
{
	int	i;

	i = game->last_item;
	if (game->file_content[i + 1] == NULL)
		return (1);
	while (game->file_content[i])
	{
		if (empty_line(game->file_content[i]) == 1)
			return (2);
		i++;
	}
	return (0);
}

static int	check_newline(char *new_line, int empty, int fd)
{
	while (new_line)
	{
		if (new_line && empty == 1)
			return (1);
		if ((new_line == NULL || new_line[0] == '\n') && empty == 0)
			empty = 1;
		free(new_line);
		new_line = get_next_line(fd);
	}
	return (0);
}

int	check_empty_line(t_game *game, char *mapfile)
{
	int		fd;
	char	*new_line;
	int		empty;
	int		j;

	j = -1;
	empty = 0;
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		return (1);
	new_line = get_next_line(fd);
	while (++j < game->last_item + 2 || new_line[0] == '\n' || new_line == NULL)
	{
		free(new_line);
		new_line = get_next_line(fd);
	}		
	return (check_newline(new_line, empty, fd));
	return (0);
}
