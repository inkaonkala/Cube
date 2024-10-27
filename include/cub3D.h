/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/10/24 19:18:19 by yhsu             ###   ########.fr       */
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

// Forward declaration of t_game
typedef struct s_game t_game;

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
	//char			**file_content_newline;
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
	
	size_t 			longest;
	int 			last_item;
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

//get_2d_array
char **get_2d_array( char *mapfile);
char *readfile(char *mapfile);

//check_elements
int check_elements_info(t_game *game,char **file_content, t_flag *flags);
int empty_line(char * file);

//create_map
int create_map(t_game * game, char **file_content);
void create_rectagle(t_game *game);
void copy_string( char *s1, char *s2);
int count_mapline(char **file_content);

//flags
int set_flags(char *file_line, t_flag *flags);
void init_flags(t_flag *flags);

//map validation
void map_validate(t_game *game);
char **copy_grid(t_game *game, char **map);

//position extention
int check_file_extesion(char *filename);
int check_texture_extension(t_game *game);
void check_player_position(t_game *game, char ** map);

//save color 
int save_colors(t_game *game, char **file_content);

//set color
void find_color(char **c_split, char **f_split, t_game *game);
void set_color(t_game *game);

//init_game
void init_game(t_game *game, char *mapfile);
int empty_line(char * file);

//error
void 	err_message_exit(char * message);
void err_message(char * message);
void free_grid(char **grid);
void clean_all_exit(t_game *game, char *message);




#endif