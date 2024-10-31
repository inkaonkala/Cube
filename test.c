
# define WIN_X		900
# define WIN_Y		700
# define WIN_TITLE	"Awesome cub3D"

# define M_PI_PI	6.28318530717958647692
# define M_SQRT2_2	0.70710678118654752440

# define FOV		1.04719755119659774615
# define SPEED_ROT	0.03141592653589793238
# define SPEED_MOV	0.05
# define N_RAYS		300

# define KEY_ESC	53
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

# define SAND       0xF7E9DB
# define RED        0xBB4211
# define RUSSIANRED 0xde300b
# define BROWN      0x54310F
# define CHOCO      0x351C04
# define MINISIDE   10
# define MINIPAD    16

typedef struct s_list	t_list;
typedef unsigned int	t_color;

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA,
	NONE
}	t_dir;

typedef struct s_cub_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	t_list	*raw_map;
}	t_cub_data;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_line_equation
{
	double	a;
	double	b;
	double	c;
}	t_line;

typedef struct s_mlx_img
{
	int		w;
	int		h;
	void	*img;
	char	*addr;
	int		bpp;
	int		line;
	int		end;
}	t_img;

typedef struct s_player
{
	t_vector	pos;
	double		dir;
	bool		move_no;
	bool		move_so;
	bool		move_we;
	bool		move_ea;
	bool		rotate_l;
	bool		rotate_r;
	bool		mouse_rotating;
}	t_player;

typedef struct s_shape
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_shape;

typedef struct s_game
{
	char		**map;
	int			map_w;
	int			map_h;
	t_player	p;
	void		*ptr;
	void		*win;
	t_img		scr;
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	t_color		flo;
	t_color		cei;
	bool		minimap_drawable;
}	t_game;

typedef struct s_ray
{
	double		angle_rel;
	double		angle_abs;
	double		wall_dist;
	t_dir		wall_dir;
	t_vector	end;
	int			wall_height;
	int			draw_height;
}	t_ray;

#endif



void	rect(t_img *img, t_shape shape, int color)
{
	int	i;
	int	j;

	i = shape.y;
	while (i < shape.y + shape.height && i < img->w)
	{
		j = shape.x;
		while (j < shape.x + shape.width && j < img->h)
		{
			put_px(i, j, color, img);
			++j;
		}
		++i;
	}
	return ;
}

void	draw_line(t_img *img, t_vector s, t_vector e, double angle)
{
	double	deltax;
	double	deltay;
	int		pixels;

	deltax = cos(angle);
	deltay = sin(angle);
	pixels = round(sqrt(pow(s.x - e.x, 2) + pow(s.y - e.y, 2))) + 2;
	while (pixels && s.x > 0 && s.y > 0 && s.x < img->w && s.y < img->h)
	{
		put_px((int)s.x, (int)s.y, 0xD5A576, img);
		s.x += deltax;
		s.y += deltay;
		--pixels;
	}
	return ;
}

void	circle(t_img *img, t_shape s, int color)
{
	int		i;
	int		j;
	double	dist;

	i = s.y;
	while (i < s.y + s.height && i < img->w)
	{
		j = s.x;
		while (j < s.x + s.width && j < img->h)
		{
			dist = sqrt(pow(i - (s.y + s.height / 2), 2)
					+ pow(j - (s.x + s.width / 2), 2));
			if (dist < s.width / 2.0)
				put_px(i, j, color, img);
			++j;
		}
		++i;
	}
	return ;
}

static inline void
	draw_minimap_floor(t_game *game, int sx, int sy, t_shape shape)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	shape.width = MINISIDE;
	shape.height = MINISIDE;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			shape.x = y * MINISIDE + sx;
			shape.y = x * MINISIDE + sy;
			if (game->map[y][x] && game->map[y][x] == '0')
				rect(&game->scr, shape, SAND);
			x++;
		}
		y++;
	}
	return ;
}

static inline void	draw_mini_raycast(t_game *g, t_ray *rays, int sx, int sy)
{                        
	t_vector	render;
	t_vector	renderend;
	int			j;

	render.x = g->p.pos.x * MINISIDE + sy;
	render.y = g->p.pos.y * MINISIDE + sx;
	j = 0;
	while (j < N_RAYS)
	{
		renderend.x = rays[j].end.x * MINISIDE + sy;
		renderend.y = rays[j].end.y * MINISIDE + sx;
		draw_line(&g->scr, render, renderend, rays[j].angle_abs);
		j++;
	}
	return ;
}

static inline void
	draw_walls_minimap(t_game *game, int sx, int sy, t_shape shape)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			shape.x = y * MINISIDE + sx + 6;
			shape.y = x * MINISIDE + sy;
			if (game->map[y][x] && game->map[y][x] == '1')
				rect(&game->scr, shape, CHOCO);
			shape.x = y * MINISIDE + sx;
			shape.y = x * MINISIDE + sy;
			if (game->map[y][x] && game->map[y][x] == '1')
				rect(&game->scr, shape, BROWN);
			x++;
		}
		y++;
	}
	return ;
}

static inline void
	draw_player_minimap(t_game *game, t_shape s, int sx, int sy)
{                       //(game, shape, startx, starty);
	s.width = 8;
	s.height = s.width;
	s.x = (int)(game->p.pos.y * MINISIDE + sx - s.width / 2);
	s.y = (int)(game->p.pos.x * MINISIDE + sy - s.height / 2);
	circle(&game->scr, s, RED);
	s.width = 6;
	s.height = s.width;
	s.x = (int)(game->p.pos.y * MINISIDE + sx - s.width / 2);
	s.y = (int)(game->p.pos.x * MINISIDE + sy - s.height / 2);
	circle(&game->scr, s, 0xF97A6D);
	return ;
}

void	draw_minimap(t_game *game, t_ray *rays)
{
	t_shape	shape;
	int		starty;//計算小地圖在畫布上的起始位置
	int		startx;

	if (!game->minimap_drawable)
		return ;
	shape.x = 0;
	shape.width = MINISIDE;
	shape.height = MINISIDE;
	starty = game->scr.w - (game->map_w * MINISIDE + MINIPAD);
    //game->scr.w：表示遊戲畫布的總寬度
    //game->map_w：表示地圖的寬度
	startx = game->scr.h - (game->map_h * MINISIDE + MINIPAD + 6);
	draw_minimap_floor(game, startx, starty, shape);
	draw_mini_raycast(game, rays, startx, starty);
	draw_walls_minimap(game, startx, starty, shape);
	draw_player_minimap(game, shape, startx, starty);
	return ;
}