/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:27:22 by brunogue          #+#    #+#             */
/*   Updated: 2025/09/29 15:27:24 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_c_p_e(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_colect, x * 32, y * 32);
	else if (game->map[y][x] == 'P')
	{
		game->x_player = x;
		game->y_player = y;
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_player, x * 32, y * 32);
	}
	else if (game->map[y][x] == 'E')
	{
		if (game->n_colect == 0)
		{
			mlx_destroy_image(game->mlx, game->img_exit);
			game->img_exit = mlx_xpm_file_to_image(
					game->mlx, "assets/images/E2.xpm",
					&game->img_w, &game->img_h);
		}
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_exit, x * 32, y * 32);
	}
}

static void	endgame1(t_game *game)
{
	int	pos_x;
	int	pos_y;

	pos_x = (game->map_w / 2) - (game->img_victory_w / 2);
	pos_y = (game->map_h / 2) - (game->img_victory_h / 2);
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->img_victory,
		pos_x, pos_y);
}

int	render_map(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	if (game->endgame == 1)
	{
		endgame1(game);
		return (0);
	}
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_wall, x * 32, y * 32);
			else if (game->map[y][x] == '0')
				mlx_put_image_to_window(game->mlx, game->win,
					game->img_backgroud, x * 32, y * 32);
			else
				render_c_p_e(game, x, y);
		}
	}
	return (0);
}
