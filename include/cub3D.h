/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/18 16:04:55 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#  ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>



# define WINDOW_WIDTH 1000
# define WINDOW_WIDTH 1000



typedef struct s_flag
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
	int duplicate;
	int all_flags;
}	t_flag;

typedef struct s_rays
{	
	float	n_ray; // float can hold decimals ->fractional numbers
	float	ray_angl;
	bool	wall_flag;
	int		distance;

	float	horizon_inter;
	float	vertical_inter;
	
}	t_rays;

typedef struct s_game
{
	char			**file_content;
	char 			**map;
	char 			*no_texture_path;//./maps/photo.png
	char 			*so_texture_path;
	char 			*we_texture_path;
	char 			*ea_texture_path;
	char			*floor_color;
	char			*ceiling_color;
	char			**f_split;// save number without ,
	char			**c_split;
	uint32_t		f_r;//save color rgb  eg.number 0
	uint32_t		f_g;//255
	uint32_t		f_b;//255
	uint32_t		c_r;
	uint32_t		c_g;
	uint32_t		c_b;
	
	int 			index;
	t_flag 			*flags;
	size_t 			height;
	size_t 			width;
	size_t			player_x;
	size_t			player_y;
	
	
	mlx_t			*mlx;
	mlx_image_t		*canvas;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	
	t_rays		*ray;
	
}	t_game;

int check_file_extesion(char *filename);
void init_game(t_game *game, char *mapfile);

void 	err_message_exit(char * message);
void err_message(char * message);

#endif