/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/17 14:02:16 by iniska           ###   ########.fr       */
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
# define TILE 30

# define FOW 60 // fieald of view
# define PI 3.14159

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
	float	n_ray; // float can hold decimals ->fractional numbers
	float	ray_angl;
	bool	wall_flag;
	int		distance;

	float	horizon_inter;
	float	vertical_inter;
	
}	t_rays;

typedef struct s_game
{
	char 			**map;
	t_flag 			*flags;
	size_t 			height;
	size_t 			width;
	size_t			player_x;
	size_t			player_y;
	float			player_angl; //Where is player facing

	float			fow; // field of view
	
	mlx_t			*mlx;
	mlx_image_t		*canvas;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	
	t_rays 			*rays;
	
}	t_game;

void	init_game(void);

void 	err_message_exit(char * message);

void	screenpop(t_game *game);

void	move_and_beam(void *data);
void 	raycast(t_game *game);

// math_stuff
void	count_values(t_game *sgame);

#endif