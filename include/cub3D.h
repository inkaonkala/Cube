/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/16 13:24:01 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#  ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"
# include"../libft/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000

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

typedef struct s_rays
{
	float	n_ray;
	
}	t_rays;

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
	
	t_rays 		*rays;
	
}	t_game;

void	init_game(void);

void 	err_message_exit(char * message);

void	screenpop(t_game *game);

#endif