/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:46:49 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/22 17:48:40 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_flags(t_flag *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->f = 0;
	flags->c = 0;
	flags->duplicate = 0;
	flags->all_flags = 0;
	flags->game = NULL;
}

static int	set_flag(char *file_line, t_flag *flags,
			int *flag, char **texture_path)
{
	if (*flag == 1)
	{
		flags->duplicate = 1;
		return (1);
	}
	*flag = 1;
	flags->all_flags++;
	if (*texture_path)
		free(*texture_path);
	if (file_line != NULL)
		*texture_path = ft_strtrim(file_line + 3, " ");
	return (0);
}

int	set_flags(char *file_line, t_flag *flags)
{
	if (*file_line == ' ' || *file_line == '\t')
		file_line++;
	if (ft_strncmp(file_line, "NO ", 3) == 0)
		return (set_flag(file_line, flags, &flags->no,
				&flags->game->no_texture_path));
	if (ft_strncmp(file_line, "WE ", 3) == 0)
		return (set_flag(file_line, flags, &flags->we,
				&flags->game->we_texture_path));
	if (ft_strncmp(file_line, "SO ", 3) == 0)
		return (set_flag(file_line, flags, &flags->so,
				&flags->game->so_texture_path));
	if (ft_strncmp(file_line, "EA ", 3) == 0)
		return (set_flag(file_line, flags, &flags->ea,
				&flags->game->ea_texture_path));
	if (ft_strncmp(file_line, "F ", 2) == 0)
		return (set_flag(file_line, flags, &flags->f,
				&flags->game->floor_color));
	if (ft_strncmp(file_line, "C ", 2) == 0)
		return (set_flag(file_line, flags, &flags->c,
				&flags->game->ceiling_color));
	return (0);
}
