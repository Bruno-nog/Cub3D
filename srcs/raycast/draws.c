/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:42:22 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/01 18:01:24 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
		draw_vision(game, ray_x, ray_y, i);
}

