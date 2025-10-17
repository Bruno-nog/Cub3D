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

t_global	*gg(void)
{
	static t_global	global;

	return (&global);
}

static bool	verify_argument(int ac)
{
	if (ac == 1)
	{
		ft_putstr("Error: Missing arguments\n");
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;
	bool	is_cub;

	if (!verify_argument(ac))
		return (0);
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
