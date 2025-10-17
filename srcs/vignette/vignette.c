/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vignette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:25:22 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/17 14:18:51 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	darken_color(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	if (factor < 0.0)
		factor = 0.0;
	if (factor > 1.0)
		factor = 1.0;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r *= factor;
	g *= factor;
	b *= factor;
	return (r << 16 | g << 8 | b);
}

static int	allocate_vignette_rows(t_game *game)
{
	int	y;

	game->vig_map = malloc(sizeof(float *) * HEIGHT);
	if (game->vig_map == NULL)
		return (0);
	y = 0;
	while (y < HEIGHT)
	{
		game->vig_map[y] = malloc(sizeof(float) * WIDTH);
		if (game->vig_map[y] == NULL)
		{
			while (--y >= 0)
				free(game->vig_map[y]);
			free(game->vig_map);
			return (0);
		}
		y++;
	}
	return (1);
}

static float	clampf(float v, float lo, float hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static void	fill_vignette(t_game *game, float max_dist)
{
	int		y;
	int		x;
	float	dx;
	float	dy;
	float	dist;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dx = x - (WIDTH / 2.0f);
			dy = y - (HEIGHT / 2.0f);
			dist = sqrtf(dx * dx + dy * dy);
			game->vig_map[y][x] = clampf(1.0f - (dist / max_dist), 0.2f, 1.5f);
			x++;
		}
		y++;
	}
}

void	init_vignette(t_game *game)
{
	float	max_dist;

	if (allocate_vignette_rows(game) == 0)
		return ;
	max_dist = WIDTH * 0.35f;
	fill_vignette(game, max_dist);
}
