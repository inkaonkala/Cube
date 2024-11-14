/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:49:10 by iniska            #+#    #+#             */
/*   Updated: 2024/11/14 11:20:26 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	update_enemy(t_game *game)//, double horizon_line, double vertical_line)
{
	double	enemy_hi;
//    double  enemy_width;
	double	top_pixl;
	double	bot_pixl;
	double	x;
	double	y;
	int		pos;
	mlx_texture_t *pic;
	uint32_t *pixels;

	// Calculate enemy size based on distance
	enemy_hi = fabs((TILE / game->enemy->distance) * (WINDOW_WIDTH) / tan(game->fow));
	
	
	
	
	bot_pixl = (WINDOW_HEIGHT / 2) + (enemy_hi);
	top_pixl = (WINDOW_HEIGHT / 2) - (enemy_hi);

	// Clamp enemy vertical position within window bounds
	if (bot_pixl > WINDOW_HEIGHT)
		bot_pixl = WINDOW_HEIGHT;
	if (top_pixl < 0)
		top_pixl = 0;

	// Choose the enemy animation frame
	pic = game->enemy->ghost_sheet;
	pixels = (uint32_t *)pic->pixels;

	// Get the specific animation frame coordinates
	x = game->enemy->col * game->enemy->len;
	y = game->enemy->row * game->enemy->height;

	// Render enemy to screen in vertical slice
	while (top_pixl < bot_pixl)
	{
		// Calculate the position in the enemy sprite sheet
		pos = (int)(y + (top_pixl - (WINDOW_HEIGHT / 2 - enemy_hi)) * (pic->height / enemy_hi)) * (game->enemy->len / 2) + (int)x;

		if (pos >= 0 && pos < (int)(pic->width * pic->height))
        {
			uint32_t pixel_color = pixels[pos];
			uint8_t alpha = (pixel_color >> 24) & 0xFF;
			if (alpha > 0)
				mlx_put_pixel(game->canvas, game->rays->i, top_pixl, pixels[pos]);
        }
		top_pixl++;
	}
}

/*
//CLANKY VERSION
void	draw_enemy(t_game *game, int frame_w, int frame_l)
{
	uint32_t 	*pixels;
	int			x;
	int			y;
	int			dest_x = 0;
	int			dest_y = 0;
	int			src_pos;

	pixels = (uint32_t *)game->enemy->ghost_sheet->pixels;
	game->enemy->x_offset = game->enemy->col * frame_w;
	game->enemy->y_offset = game->enemy->row * frame_l;
	y = 0;
	while(y < frame_l)
	{
		x = 0;
		while (x < frame_w)
		{
			src_pos = (game->enemy->y_offset + y) * game->enemy->ghost_sheet->width + (game->enemy->x_offset + x);
			game->enemy->color = pixels[src_pos];
			mlx_put_pixel(game->enemy->ghosty, dest_x + x, dest_y + y, game->enemy->color);
			x++;
		}
		y++;
	}
}

void	update_enemy(t_game *game)
{
	double	enemy_hi;
	double	top_pixl;
	double	bot_pixl;
	double	start_x;
	double	end_x;

	// Calculate enemy size based on distance
	enemy_hi = fabs((TILE / game->enemy->distance) * (WINDOW_WIDTH) / tan(game->fow));
	bot_pixl = (WINDOW_HEIGHT / 2) + (enemy_hi / 2);
	top_pixl = (WINDOW_HEIGHT / 2) - (enemy_hi / 2);

	// Clamp vertical bounds to screen
	if (bot_pixl > WINDOW_HEIGHT) bot_pixl = WINDOW_HEIGHT;
	if (top_pixl < 0) top_pixl = 0;

	// Calculate horizontal position for centering enemy on screen
	double angle_offset = game->enemy->angl - game->player_angl;
	start_x = (WINDOW_WIDTH / 2) + (angle_offset * (WINDOW_WIDTH / game->fow)) - (enemy_hi / 2);
	end_x = start_x + enemy_hi;

	// Clamp horizontal bounds to screen
	if (start_x < 0) start_x = 0;
	if (end_x > WINDOW_WIDTH) end_x = WINDOW_WIDTH;

	// Draw the correct frame using `draw_enemy`
	int frame_w = game->enemy->len;  // Width of one frame
	int frame_h = game->enemy->height;  // Height of one frame
	draw_enemy(game, frame_w, frame_h);  // Draw frame onto `game->enemy->ghosty`

	// Access pixels from the drawn enemy frame
	uint32_t *ghost_pixels = (uint32_t *)game->enemy->ghosty->pixels;

	// Render scaled enemy on the main canvas
	int x = (int)start_x;
	int dest_x = 0;
	while (x < (int)end_x)
	{
		double scale_x = (double)dest_x * frame_w / enemy_hi;
		int y = (int)top_pixl;
		int dest_y = 0;
		while (y < (int)bot_pixl)
		{
			double scale_y = (double)dest_y * frame_h / enemy_hi;
			int ghost_pos = ((int)scale_y * game->enemy->ghosty->width) + (int)scale_x;
			uint32_t color = ghost_pixels[ghost_pos];

			// Draw only non-transparent pixels
			uint8_t alpha = (color >> 24) & 0xFF;
			if (alpha > 0)
			{
				mlx_put_pixel(game->canvas, x, y, color);
			}
			y++;
			dest_y++;
		}
		x++;
		dest_x++;
	}
}


*/

/*
THIS DOES NOT WORK
static double get_setof_x(t_game *game)
{
    double x;

    // Set x to the starting x offset of the selected frame
    x = game->enemy->x_offset;

    // Scale x position based on ghostie's frame width (enemy->len)
    x = fmod(game->enemy->distance * (game->enemy->len / TILE), game->enemy->len);

    // Ensure x is within the width bounds of a single frame
    if (x < 0 || x >= game->enemy->len)
        x = 0; // Reset to 0 if out of bounds

    return x + game->enemy->x_offset;
}

void update_enemy(t_game *game, double bot_pixl, double top_pixl, double ghostie_hi)
{
    uint32_t *pixels = (uint32_t *)game->enemy->ghost_sheet->pixels;
    int frame_w = game->enemy->len;
    int frame_l = game->enemy->height;
    double x, y;
    int pos;

    // Select the frame for ghostie
    game->enemy->x_offset = game->enemy->col * frame_w;
    game->enemy->y_offset = game->enemy->row * frame_l;

    // Set initial x based on ghostie position
    x = get_setof_x(game, game->enemy->ghost_sheet);
    if (x < game->enemy->x_offset || x >= game->enemy->x_offset + frame_w)
        return;

    // Scale y position based on distance
    y = (top_pixl - (WINDOW_HEIGHT / 2) + (ghostie_hi / 2)) * frame_l / ghostie_hi + game->enemy->y_offset;
    if (y < game->enemy->y_offset || y >= game->enemy->y_offset + frame_l) return;

    while (top_pixl < bot_pixl)
    {
        pos = ((int)y * game->enemy->ghost_sheet->width) + (int)x;
        if (pos >= 0 && pos < game->enemy->ghost_sheet->width * game->enemy->ghost_sheet->height)
        {
            uint32_t pixel_color = pixels[pos];
            if (pixel_color != 0)
                mlx_put_pixel(game->canvas, game->rays->i, top_pixl, pixel_color);
        }
        y += frame_l / ghostie_hi;
        top_pixl++;
    }
}
*/



/*
void	draw_enemy(t_game *game, int frame_w, int frame_l)
{
	uint32_t 	*pixels;
	int			x;
	int			y;
	int			dest_x = 0;
	int			dest_y = 0;
	int			src_pos;

	pixels = (uint32_t *)game->enemy->ghost_sheet->pixels;
	game->enemy->x_offset = game->enemy->col * frame_w;
	game->enemy->y_offset = game->enemy->row * frame_l;
	y = 0;
	while(y < frame_l)
	{
		x = 0;
		while (x < frame_w)
		{
			src_pos = (game->enemy->y_offset + y) * game->enemy->ghost_sheet->width + (game->enemy->x_offset + x);
			game->enemy->color = pixels[src_pos];
			mlx_put_pixel(game->enemy->ghosty, dest_x + x, dest_y + y, game->enemy->color);
			x++;
		}
		y++;
	}
}

static double	get_setof_x(t_game *game, mlx_texture_t *pic)
{
	double	x;

	x = 0;
	if (!game || !game->rays || !pic || pic->width == 0)
	{
		printf("No Picture\n");
    	return (x);
	}
	if (game->rays->wall_flag == true)//THIS
		x = (int)fmodf((game->rays->horizon_inter_x * (pic->width / TILE)), pic->width);
	else
		x = (int)fmodf((game->rays->vertical_inter_y * (pic->width / TILE)), pic->width);
	return (x);
}

static void draw_enemy2(t_game *game, double bot_pixl, double top_pixl, double wall_hi)
{
    uint32_t		*pixels;
    double			x;
	double			y;
    int				pos;

	pixels = (uint32_t *)game->enemy->ghost_sheet->pixels;
    
    x = get_setof_x(game, game->enemy->ghost_sheet);
    if (x < 0 || x >= game->enemy->ghosty->width)
        return;

    // Calculate initial y position in texture based on wall height
    y = (top_pixl - (WINDOW_HEIGHT / 2) + (wall_hi / 2)) * (double)game->enemy->ghosty->height / wall_hi;
    if (y < 0) y = 0;

    while (top_pixl < bot_pixl)
    {
        pos = (int)y * game->enemy->ghosty->width + (int)x;
        if (pos < 0 || pos >= (int)(game->enemy->ghosty->width * game->enemy->ghosty->height)) return;
        mlx_put_pixel(game->canvas, game->rays->i, top_pixl, pixels[pos]);
        y += (double)game->enemy->ghosty->height / wall_hi;
        top_pixl++;
    }
}

void update_enemy(t_game *game)
{
    double wall_hi;
    double top_pixl;
    double bot_pixl;
    int screen_x;

    // Calculate distance and angle relative to player
    size_t dis_x = game->enemy->g_x - game->rays->p_x;
    size_t dis_y = game->enemy->g_y - game->rays->p_y;

    game->enemy->distance = sqrt(dis_x * dis_x + dis_y * dis_y);
    game->enemy->angl_to_p = atan2(dis_y, dis_x);
    game->enemy->angl = game->enemy->angl_to_p - game->player_angl;

    // Calculate screen position and scaling, similar to wall calculations
    screen_x = (game->enemy->angl / (game->fow / 2)) * (WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 2);
    wall_hi = fabs((TILE / game->enemy->distance) * (WINDOW_WIDTH / 2) / tan(game->fow));
    bot_pixl = (WINDOW_HEIGHT / 2) + (wall_hi / 2);
    top_pixl = (WINDOW_HEIGHT / 2) - (wall_hi / 2);

    // Clamp top and bottom pixel positions to window boundaries
    if (bot_pixl > WINDOW_HEIGHT) bot_pixl = WINDOW_HEIGHT;
    if (top_pixl < 0) top_pixl = 0;

    // Call the adjusted draw function to render `ghostie` similarly to walls
    draw_enemy2(game, bot_pixl, top_pixl, wall_hi);
}

*/
