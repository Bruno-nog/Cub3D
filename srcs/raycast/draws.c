/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:42:22 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/07 16:26:45 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}


void	draw_square(int x, int y, int size, int color)
{
	int	i;

	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, &gg()->game);
	i = 0;
	while (i++ < size)
		put_pixel(x, y + i, color, &gg()->game);
	i = 0;
	while (i++ < size)
		put_pixel(x + size, y + i, color, &gg()->game);
	i = 0;
	while (i++ < size)
		put_pixel(x + i, y + size, color, &gg()->game);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = game->map;
	color = 0x000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, color);
			x++;
		}
		y++;
	}
}

void	draw_vision(t_game *game, float ray_x, float ray_y, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end;

	gg()->x1 = game->player.x;
	dist = fixed_dist(game->player.y, ray_x, ray_y, game);
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}

void	draw_wall_with_texture(t_game *game, int screen_x, float height, int texture_index, float wall_x)
{
	int				start_y;
	int				end_y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;
	int				y;

	gg()->x1 = game->player.x;
	start_y = (HEIGHT - height) / 2;
	if (start_y < 0)
		start_y = 0;
	end_y = start_y + height;
	if (end_y > HEIGHT)
		end_y = HEIGHT;

	tex_x = (int)(wall_x * game->texture[texture_index].width);
	for (y = start_y; y < end_y; y++)
	{
		int d = y * 256 - HEIGHT * 128 + (int)height * 128;
		tex_y = ((d * game->texture[texture_index].height) / (int)height) / 256;
		color = get_texture_color(&game->texture[texture_index], tex_x, tex_y);
		put_pixel(screen_x, y, color, game);
	}
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;
	int side;
	int texture_index;
	float wall_x;
	float	height;
	float	dist;

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if ((int)((ray_x - cos_angle) / BLOCK) != (int)(ray_x / BLOCK))
	{
		side = 1; // vertical
		texture_index = (cos_angle > 0) ? 2 : 3;
		wall_x = fmod(ray_y, BLOCK);
	}
	else
	{
		side = 0; // horizontal
		texture_index = (sin_angle > 0) ? 1 : 0;
		wall_x = fmod(ray_x, BLOCK);
	}
	if (!DEBUG)
	{
		dist = fixed_dist(game->player.y, ray_x, ray_y, game);
		height = (BLOCK / 0.6 / dist) * (WIDTH / 2);
		draw_wall_with_texture(game, i, height, texture_index, wall_x / BLOCK);
	}
}
