/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:49:37 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/13 19:15:40 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vision(t_game *game, float ray_x, float ray_y, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end;

	gg()->x1 = game->player.x;
	dist = fixed_dist(game->player.y, ray_x, ray_y, game);
	height = (BLK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 255, game);
		start_y++;
	}
}

static void	select_wall_texture(t_game *game, t_rayinfo *ray, int i)
{
	int		side;
	int		texture_index;

	if ((int)((ray->ray_x - ray->cos_angle) / BLK) != (int)(ray->ray_x / BLK))
	{
		side = 1;
		if (ray->cos_angle > 0)
			texture_index = 2;
		else
			texture_index = 3;
	}
	else
	{
		side = 0;
		if (ray->sin_angle > 0)
			texture_index = 1;
		else
			texture_index = 0;
	}
	correct_dist(game, ray, texture_index, i);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	t_rayinfo	ray;

	ray.cos_angle = cos(start_x);
	ray.sin_angle = sin(start_x);
	ray.ray_x = player->x;
	ray.ray_y = player->y;
	while (!touch(ray.ray_x, ray.ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray.ray_x, ray.ray_y, 0xFF0000, game);
		ray.ray_x += ray.cos_angle;
		ray.ray_y += ray.sin_angle;
	}
	select_wall_texture(game, &ray, i);
}
