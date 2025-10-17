/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:02:54 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/17 14:19:11 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int		index;
	float	brightness;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	brightness = game->vig_map[y][x];
	color = darken_color(color, brightness);
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(x, y, game->map_tex.ceiling, game);
			else
				put_pixel(x, y, game->map_tex.floor, game);
			x++;
		}
		y++;
	}
}

static void	get_map_size(t_game *game, int *w, int *h)
{
	int	i;

	*h = 0;
	*w = 0;
	if (!game->map)
		return ;
	while (game->map[*h] != NULL)
		(*h)++;
	if (*h > 0)
	{
		i = 0;
		while (game->map[0][i] != '\0')
			i++;
		*w = i;
	}
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;
	int	map_w;
	int	map_h;

	if (!game || !game->map)
		return (true);
	get_map_size(game, &map_w, &map_h);
	if (map_w == 0 || map_h == 0)
		return (true);
	x = (int)(px / BLK);
	y = (int)(py / BLK);
	if (x < 0 || y < 0 || x >= map_w || y >= map_h)
		return (true);
	return (game->map[y][x] == '1');
}
