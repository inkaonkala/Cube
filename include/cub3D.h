/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/28 11:36:21 by iniska           ###   ########.fr       */
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


# define WINDOW_WIDTH 1300
# define WINDOW_HEIGHT 1000
# define TILE 30 // should it be 60 or 64?

# define ROTATIO_SPEED 0.045
# define SPEED 4

# define FOW 60 // fieald of view
# define PI 3.14159


// Forward declaration of t_game
typedef struct s_game t_game;

typedef struct s_rays
{	
	float	n_ray; // float can hold decimals ->fractional numbers
	float	ray_angl;
	bool	wall_flag;
	
	float	distance;
	int		i;

	float	horizon_inter_x;
	float	horizon_inter_y;
	float	vertical_inter_x;
	float	vertical_inter_y;
	
}	t_rays;

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
	t_game *game;

}	t_flag;

typedef struct s_game
{
	char			**file_content;
	char			**file_content_newline;
	char 			**map;
	char 			*no_texture_path;//./maps/photo.png
	char 			*so_texture_path;
	char 			*we_texture_path;
	char 			*ea_texture_path;
	char			*floor_color;
	char			*ceiling_color;
	char			**f_split;// save number without ,
	char			**c_split;
	uint32_t		floor_r;//save color rgb  eg.number 0
	uint32_t		floor_g;//255
	uint32_t		floor_b;//255
	uint32_t		ceiling_r;
	uint32_t		ceiling_g;
	uint32_t		ceiling_b;
	
	int 			index;
	int 			last_item;
	int				rotation;
	bool			mouse_on;

	t_flag 			*flags;
	size_t 			height;
	size_t 			width;
	size_t			player_x;
	size_t			player_y;

	float			player_angl; //Where is player facing
	float			fow; // field of view for the player
	
	mlx_t			*mlx;
	mlx_image_t		*canvas;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	
	t_rays 			*rays;
	
}	t_game;

//void	init_game(void);

void 	err_message_exit(char * message);

void	screenpop(t_game *game);

void	move_and_beam(void *data);
void 	raycast(t_game *game);

void	set_walls(t_game *game, int ray);

// math_stuff
float	beam_angl(float angl);
void	count_values(t_game *sgame);
float	distance(t_game *game, float x, float y);

void	set_pixels(t_game *game, double x, double y, int colour);

int 	check_file_extesion(char *filename);
void 	init_game(t_game *game, char *mapfile);

void 	err_message_exit(char * message);
void 	err_message(char * message);
void 	free_grid(char **grid);
void 	clean_all_exit(t_game *game, char *message);

char	**split_newline(char const *s, char c);

void	draw_wall(t_game *game, int ray, double bot_pixl, double top_pixl);

void	keys(mlx_key_data_t key_data, void *data);
void	mouse_move(double x, double y, void *data);
void 	mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void *data);

#endif