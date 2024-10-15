/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/15 20:36:37 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#  ifndef CUB3D_H
#define CUB3D_H

#include"../libft/ft_printf.h"
#include "MLX42.h"

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
	int all_flags;
}	t_flag;

typedef struct s_raycast
{
	
}	t_raycast;

typedef struct s_game
{
	char 			**map;
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
	
	t_raycast 		*raycast;
	
}	t_game;

typedef struct s_rays
{
	
}	t_rays;


#endif