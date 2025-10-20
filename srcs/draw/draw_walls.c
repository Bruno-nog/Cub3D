/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:48:58 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/17 18:07:33 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	correct_dist(t_game *game, t_rayinfo *ray, int tex_index, int i)
{
	float		distance;
	float		height;
	float		wall_x;
	t_drawparam	dp;

	if (tex_index == 0 || tex_index == 1)
		wall_x = fmod(ray->ray_x, BLK);
	else
		wall_x = fmod(ray->ray_y, BLK);
	if (!DEBUG)
	{
		distance = fixed_dist(game->player.y, ray->ray_x, ray->ray_y, game);
		height = (BLK / 0.6 / distance) * (WIDTH / 2);
		dp.screen_x = i;
		dp.height = height;
		dp.tex_index = tex_index;
		dp.wall_x = wall_x / BLK;
		draw_wall_with_texture(game, &dp);
	}
}

static void	draw_tex_col(t_game *game, t_drawparam *p, int tex_x, int start_y)
{
	int	end_y;
	int	y;
	int	tex_y;
	int	d;

	end_y = start_y + (int)p->height;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	y = start_y;
	while (y < end_y)
	{
		d = y * 256 - HEIGHT * 128 + (int)p->height * 128;
		tex_y = ((d * game->tex[p->tex_index].height) / (int)p->height) / 256;
		put_pixel(p->screen_x, y,
			get_texture_color(&game->tex[p->tex_index], tex_x, tex_y), game);
		y++;
	}
}

void	draw_wall_with_texture(t_game *game, t_drawparam *p)
{
	int	tex_x;
	int	start_y;

	gg()->x1 = game->player.x;
	start_y = (HEIGHT - (int)p->height) / 2;
	if (start_y < 0)
		start_y = 0;
	tex_x = (int)(p->wall_x * game->tex[p->tex_index].width);
	draw_tex_col(game, p, tex_x, start_y);
}
