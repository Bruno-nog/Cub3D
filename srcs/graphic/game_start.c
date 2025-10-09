/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:49:33 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/09 14:53:15 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	start_image(t_game *game)
// {
// 	game->img_backgroud = mlx_xpm_file_to_image
// 		(game->mlx, "assets/images/0.xpm", &game->img_w, &game->img_h);
// 	game->img_wall = mlx_xpm_file_to_image
// 		(game->mlx, "assets/images/1.xpm", &game->img_w, &game->img_h);
// 	game->img_player = mlx_xpm_file_to_image
// 		(game->mlx, "assets/images/PD.xpm", &game->img_w, &game->img_h);
// 	game->img_colect = mlx_xpm_file_to_image
// 		(game->mlx, "assets/images/C.xpm", &game->img_w, &game->img_h);
// 	game->img_exit = mlx_xpm_file_to_image
// 		(game->mlx, "assets/images/E.xpm", &game->img_w, &game->img_h);
// 	game->img_victory = mlx_xpm_file_to_image
// 		(game->mlx, "assets/images/V.xpm", &game->img_victory_w,
// 			&game->img_victory_h);
// 	if (!game->img_backgroud || !game->img_wall || !game->img_player
// 		|| !game->img_colect || !game->img_exit)
// 	{
// 		ft_putstr_fd("Error\nNo image available!\n", 1);
// 		exit(1);
// 	}
// }

// static void	size_window_start(t_game *game)
// {
// 	int	i;

// 	game->map_w = ft_strlen(game->map[0]) * 32;
// 	i = 0;
// 	while (game->map[i])
// 		i++;
// 	game->map_h = i * 32;
// }

// void	game_start(t_game *game)
// {
// 	game->mlx = mlx_init();
// 	size_window_start(game);
// 	game->win = mlx_new_window(game->mlx, 10, 10, "Cub3D");
// 	game->moves = 0;
// 	put_moves(game);
// 	game->endgame = 0;
// 	game->moves = 1;
// }

// start_image(game);
// render_map(game);
