/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:27:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/01 10:58:35 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x, y + i, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + size, y + i, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + i, y + size, color, game);
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
				draw_square(x * 64, y * 64, 64, color, game);
			x++;
		}
		y++;
	}
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
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

char	**get_map(void)
{
	char **map = malloc(sizeof(char *) * 11);

	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100001000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	// colocar minha inplemenatacoa
	game->map = get_map();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		ray_x;
	float		ray_y;
	float		cos_angle;
	float		sin_angle;

	player = &game->player;
	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, 10, 0x00FF00, game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
