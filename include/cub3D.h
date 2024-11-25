/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:55:19 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/25 13:55:18 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include"../libft/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define WIN_WIDTH 1024
# define WIN_HEI 1024
# define TILE 64

# define ROTATIO_SPEED 0.045
# define SPEED 3
# define FOW 60
# define PI 3.14159265
# define SAND       0xF7E9DB
# define RED        0xBB4211
# define RUSSIANRED 0xde300b
# define BROWN      0x54310F
# define CHOCO      0x351C04
# define BACKGROUND_COLOR 0xFFE5E4E4
# define MINIMAP_SIDE 208
# define MINIMAP_TILE_COUNT 13
# define MINIMAP_IMAGE_SIDE 16

# ifndef USE_BONUS
#  define BONUS 0
# else
#  define BONUS 1
# endif

# define GP "./textures/ghosty.png"
# define WINIMA	"./textures/winning.png"
# define DOOR_PATH_CLOSE "./textures/door_closed_0.png"
# define DOOR_PATH_OPEN "./textures/door_opening_1.png"
# define GAMEOVERI "./textures/gameover.png"

typedef struct s_game	t_game;

typedef struct s_shape
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_shape;

typedef struct s_minimap
{
	mlx_image_t		*background;
	t_game			*game;
	mlx_t			*mlx;
	mlx_image_t		*image;
	size_t			px;
	size_t			py;
}	t_minimap;

typedef struct s_g
{
	char			*ghost_pic;
	mlx_texture_t	*ghost_sheet;
	mlx_image_t		*ghosty;
	size_t			g_x;
	size_t			g_y;
	int				height;
	int				len;
	uint32_t		color;
	int				row;
	int				col;
	int				screen_x;
	double			x_offset;
	double			y_offset;
	float			angl;
	float			distance;
	float			angl_to_p;
	mlx_texture_t	*pic;
	uint32_t		*pixels;
	int				frame_x;
	int				frame_y;
}	t_g;

typedef struct s_rays
{	
	float	n_ray;
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
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	int		duplicate;
	int		all_flags;
	t_game	*game;
}	t_flag;

typedef struct s_game
{
	char			**file_content;
	char			**map;
	char			*no_texture_path;
	char			*so_texture_path;
	char			*we_texture_path;
	char			*ea_texture_path;
	char			*floor_color;
	char			*ceiling_color;
	char			**f_split;
	char			**c_split;
	uint32_t		floor_r;
	uint32_t		floor_g;
	uint32_t		floor_b;
	uint32_t		ceiling_r;
	uint32_t		ceiling_g;
	uint32_t		ceiling_b;
	size_t			longest;
	int				last_item;
	bool			mouse_on;
	bool			horizon;
	bool			death;
	bool			win;
	int				rotation;
	int				up_down;
	int				left_right;
	t_flag			*flags;
	size_t			height;
	size_t			width;
	size_t			player_x;
	size_t			player_y;
	float			mini_angle;
	float			player_angl;
	float			fow;
	mlx_t			*mlx;
	mlx_image_t		*canvas;
	mlx_texture_t	*miniplayer_text;
	mlx_image_t		*mini_player;
	mlx_image_t		*minimap;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	t_rays			*rays;
	t_g				*g;
	char			s;
	char			d;
	bool			door_state;
	bool			hit_door;
	size_t			door_x;
	size_t			door_y;
	mlx_texture_t	*door_open_texture;
	mlx_texture_t	*door_close_texture;
	mlx_image_t		*door;
	mlx_image_t		*gameover_image;
}	t_game;

//get_2d_array
char		**get_2d_array( char *mapfile);
char		*readfile(char *mapfile);

//check_elements
int			check_elements_info(t_game *game, char **file_content,
				t_flag *flags);
int			empty_line(char *file);

//create_map
int			create_map(t_game *game, char **file_content);
void		create_rectagle(t_game *game);

//void copy_string( t_game *ame, char *s1, char *s2);
void		copy_string( char *s1, char *s2);
int			count_mapline(char **file_content);

//flags
int			set_flags(char *file_line, t_flag *flags);
void		init_flags(t_flag *flags);

//map validation
void		map_validate(t_game *game);
char		**copy_grid(t_game *game, char **map);
int			check_map_closed(t_game *game, char **map);

//position extention
int			check_file_extesion(char *filename);
int			check_texture_extension(t_game *game);
void		check_player_position(t_game *game, char **map);

//save color
void		colour_flip(uint32_t *pixels, int width, int height);
int			save_colors(t_game *game, char **file_content);

//set color
void		find_color(char **c_split, char **f_split, t_game *game);
void		set_color(t_game *game);

//init_game
void		init_game(t_game *game, char *mapfile);
int			empty_line(char *file);
int			check_empty_line(t_game *game, char *mapfile);
int			check_empty_map(t_game *game);

//error
void		err_message_exit(char *message);
void		screenpop(t_game *game);

//move_and_beam
void		move_and_beam(void *data);

//move_hook
void		move_hook(t_game *game, double move_x, double move_y);
void		raycast(t_game *game);
void		set_walls(t_game *game, int ray);

//move_helpers
void		death_checker(t_game *game, double radius);
bool		valid(t_game *game, int y, int x, int i);

// math_stuff
float		beam_angl(float angl);
void		count_values(t_game *sgame);
float		distance(t_game *game, float x, float y);

int			check_file_extesion(char *filename);
void		init_game(t_game *game, char *mapfile);

void		err_message_exit(char *message);
void		err_message(char *message);
void		free_grid(char **grid);

//clean up 
void		clean_all_exit(t_game *game, char *message);
void		clean_all(t_game *game);
void		delete_image(t_game *game);
void		free_texture(t_game *game);
void		free_grid(char **grid);

//ray_helpers
int			wall(t_game *game, float x, float y, bool *ghosty);
int			move_ray(float angl, float *inter, float *step, int is_vert);

//drawing_helpers
double		get_setof_x(t_game *game, mlx_texture_t *pic);
void		set_pixels(t_game *game, double x, double y, int colour);

//render_wall
void		draw_wall(t_game *game, double bot_pixl, double top_pixl,
				double wall_hi);

//keys
void		wasd(t_game *game, double *move_x, double *move_y);
void		keys(t_game *game);
void		mouse_move(double x, double y, void *data);
void		mouse_press(mouse_key_t button, action_t action,
				modifier_key_t mods, void *data);

//BONUS
//mini_map
void		draw_mini_map(t_game *game);
void		draw_player(t_game *game);

// ghosty 

void		ghostie(t_game *game);
void		update_g(t_game *game);
void		animate(t_game *game);
void		set_ghost(t_game *game);
void		game_over_image(t_game *game);

//door 
void		check_door(t_game *game);
void		init_door(t_game *game);
void		check_door_position(t_game *game, char **map);

uint32_t	swap_rgb_bgr(uint32_t color);

#endif