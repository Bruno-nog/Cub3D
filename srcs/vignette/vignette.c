/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vignette.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:25:22 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/12 19:01:28 by brunogue         ###   ########.fr       */
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

void	init_vignette(t_game *game)
{
	int		x;
	int		y;
	float	dist;
	float	max_dist;
	float	factor;

	game->vignette_map = malloc(sizeof(float *) * HEIGHT);
	if (!game->vignette_map)
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		game->vignette_map[y] = malloc(sizeof(float) * WIDTH);
		y++;
	}
	max_dist = WIDTH * 0.35;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < 1280)
		{
			dist = sqrt(pow(x - (WIDTH / 2.0), 2) + pow(y - (HEIGHT / 2.0), 2));
			game->vignette_map[y][x] = 1.0 - (dist / max_dist);
			factor = 1 - (dist / max_dist);
			if (factor < 0.2)
				factor = 0.2;
			if (factor > 1.5)
				factor = 1.5;
			game->vignette_map[y][x] = factor;
			x++;
		}
		y++;
	}
}
