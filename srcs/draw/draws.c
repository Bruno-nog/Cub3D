/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:42:22 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/13 13:33:51 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <sys/time.h>

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

void	draw_scene(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	clear_image(game);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00);
		draw_map(game);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
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

int	draw_loop(t_game *game, t_player *player)
{
	static struct timeval	last = {0, 0};
	struct timeval			now;
	double					now_s;
	double					last_s;
	double					dt;

	player = &game->player;
	if (last.tv_sec == 0 && last.tv_usec == 0)
		gettimeofday(&last, NULL);
	gettimeofday(&now, NULL);
	now_s = (double)now.tv_sec + (double)now.tv_usec / 1000000.0;
	last_s = (double)last.tv_sec + (double)last.tv_usec / 1000000.0;
	dt = now_s - last_s;
	if (dt < 0.0)
		dt = 0.0;
	if (dt > 0.1)
		dt = 0.1;
	last = now;
	move_player(player, dt);
	draw_scene(game);
	return (0);
}

// static void	correct_dist(t_game *game, t_rayinfo *ray, int tex_index, int i)
// {
// 	float	distance;
// 	float	height;
// 	float	wall_x;

// 	if (tex_index == 0 || tex_index == 1)
// 		wall_x = fmod(ray->ray_x, BLK);
// 	else
// 		wall_x = fmod(ray->ray_y, BLK);
// 	if (!DEBUG)
// 	{
// 		distance = fixed_dist(game->player.y, ray->ray_x, ray->ray_y, game);
// 		height = (BLK / 0.6 / distance) * (WIDTH / 2);
// 		draw_wall_with_texture(game, i, height, tex_index, wall_x / BLK);
// 	}
// }
// void	draw_wall_with_texture(t_game *game, int screen_x, float height, int texture_index, float wall_x)
// {
// 	int				start_y;
// 	int				end_y;
// 	int				tex_x;
// 	int				tex_y;
// 	unsigned int	color;
// 	int				y;

// 	gg()->x1 = game->player.x;
// 	start_y = (HEIGHT - height) / 2;
// 	if (start_y < 0)
// 		start_y = 0;
// 	end_y = start_y + height;
// 	if (end_y > HEIGHT)
// 		end_y = HEIGHT;
// 	tex_x = (int)(wall_x * game->texture[texture_index].width);
// 	y = start_y;
// 	while (y < end_y)
// 	{
// 		int d = y * 256 - HEIGHT * 128 + (int)height * 128;
// 		tex_y = ((d * game->texture[texture_index].height) / (int)height) / 256;
// 		color = get_texture_color(&game->texture[texture_index], tex_x, tex_y);
// 		put_pixel(screen_x, y, color, game);
// 		y++;
// 	}
// }