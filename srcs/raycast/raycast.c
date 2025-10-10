/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2025/10/01 17:43:08 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/01 18:41:47 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stddef.h>



void	put_pixel(int x, int y, int color, t_game *game)
{
	int		index;
	float	brightness;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	brightness = game->vignette_map[y][x];
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
	// game->ceiling = 0x0AD2FA;
	game->floor = 0x240606;
	// game->ceiling = 0x0F0F0F;
	game->ceiling = 0x050547;
	// game->floor = 0x1A0707;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(x, y, game->ceiling, game);
			else
				put_pixel(x, y, game->floor, game);
			x++;
		}
		y++;
	}
}




bool	init_game(t_game *game, char *av)
{
	char	**map;
	size_t	count;
	char	*line;

	count = 0;
	map = NULL;
	line = NULL;
	game->mlx = mlx_init();
	game->map = read_map(av, map, count, line);
	if (game->map == NULL)
		return (false);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (true);
}

static void get_map_size(t_game *game, int *w, int *h)
{
	int i;

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

bool touch(float px, float py, t_game *game)
{
	int x;
	int y;
	int map_w;
	int map_h;

	if (!game || !game->map)
		return (true);
	get_map_size(game, &map_w, &map_h);
	if (map_w == 0 || map_h == 0)
		return (true);

	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (x < 0 || y < 0 || x >= map_w || y >= map_h)
		return (true);
	return (game->map[y][x] == '1');
}
