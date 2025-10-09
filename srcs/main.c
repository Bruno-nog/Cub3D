/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:27:26 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/01 17:53:51 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

t_global	*gg(void)
{
	static t_global	global;

	return (&global);
}

// int	draw_loop(t_game *game)
// {
// 	t_player	*player;
// 	float		fraction;
// 	float		start_x;
// 	int			i;

// 	player = &game->player;
// 	move_player(player);
// 	clear_image(game);
// 	if (DEBUG)
// 	{
// 		draw_square(player->x, player->y, 10, 0x00FF00);
// 		draw_map(game);
// 	}
// 	fraction = PI / 3 / WIDTH;
// 	start_x = player->angle - PI / 6;
// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		draw_line(player, game, start_x, i);
// 		start_x += fraction;
// 		i++;
// 	}
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	return (0);
// }

int	draw_loop(t_game *game)
{
	t_player				*player;
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

int	main(int ac, char **av)
{
	t_game	game;
	bool	is_cub;

	if (ac == 1)
	{
		ft_printf("ERROR: Missing arguments\n");
		return (0);
	}
	is_cub = main_parser(av[1]);
	if (!is_cub)
		return (0);
	if (!init_game(&game, av[1]))
		return (0);
	gg()->game = game;
	init_player(&game.player);
	load_all_textures(&game);
	init_vignette(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
