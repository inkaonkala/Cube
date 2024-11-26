/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:02:51 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/26 11:53:18 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	parse_element(t_game *game, t_flag *flags, char *mapfile)
{
	if (check_elements_info(game, game->file_content, flags) == 1)
	{
		free(game->flags);
		clean_all_exit(game, "invalid Elementssss");
	}
	free(game->flags);
	if (check_texture_extension(game) == 0)
		clean_all_exit(game, "please provide a '.png' texture");
	save_colors(game, game->file_content);
	set_color(game);
	if (check_empty_map(game) == 1)
		clean_all_exit(game, "The map is EMPTY!");
	else if (check_empty_map(game) == 2)
		clean_all_exit(game, "Tha map has an empty line.");
	if (check_empty_line(game, mapfile) == 1)
		clean_all_exit(game, "Tha map has empty line(s).");
	if (create_map(game, game->file_content + (game->last_item + 1)) == 1)
		clean_all_exit(game, "The map's memory allocation failed");
	return (0);
}

static void	parse_file(t_game *game, char *mapfile)
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
	{
		free(game->flags);
		clean_all_exit(game, "The file is empty!");
	}
	parse_element(game, game->flags, mapfile);
}

void	init_game(t_game *game, char *mapfile)
{
	game->death = false;
	game->win = false;
	parse_file(game, mapfile);
	map_validate(game);
	create_rectagle(game);
	check_player_position(game, game->map);
}
