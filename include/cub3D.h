/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/04 14:53:01 by yhsu             ###   ########.fr       */
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
# define TILE 64 // should it be 60 or 64?

# define ROTATIO_SPEED 0.045
# define SPEED 3

# define FOW 60 // fieald of view
# define PI 3.14159265

//for mini map

# define SAND       0xF7E9DB
# define RED        0xBB4211
# define RUSSIANRED 0xde300b
# define BROWN      0x54310F
# define CHOCO      0x351C04
#define BACKGROUND_COLOR 0xFFE5E4E4
# define MINIMAP_SIDE 200//小地圖中每個方格的邊長
# define MINIMAP_COVERAGE 10// 小地圖的比例或縮放比例
# define MINIMAP_PADDING 0// 小地圖與視窗邊緣的間距為16像素



// Forward declaration of t_game
typedef struct s_game t_game;

typedef struct s_shape
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_shape;



typedef struct s_minimap
{
	mlx_image_t* background;
	t_game *game;
	mlx_t	*mlx;
	mlx_image_t* image;
	size_t			px;
	size_t			py;

}	t_minimap;

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

	int		p_x;
	int		p_y;
	
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



//game->map[game->rays->p_x][game->rays->p_y]

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
	
	size_t 			longest;//width
	int 			last_item;
	bool			mouse_on;
	bool			horizon;

	//it got moves
	int				rotation;
	int				up_down;
	int				left_right;

	t_flag 			*flags;
	size_t 			height;
	
	size_t			player_x;
	size_t			player_y;

	float			player_angl; //Where is player facing
	float			fow; // field of view for the player
	
	mlx_t			*mlx;
	mlx_image_t		*canvas;
	mlx_image_t	    *minimap;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	
	t_rays 			*rays;
	
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
void copy_string( t_game *ame, char *s1, char *s2);
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

//mini_map

void create_minimap(t_game *game);



void	draw_wall(t_game *game, int ray, double bot_pixl, double top_pixl);


void	keys(t_game *game);
void	mouse_move(double x, double y, void *data);
void 	mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void *data);

#endif