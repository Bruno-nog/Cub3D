/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:59:50 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/16 15:22:37 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_variables(t_game *game)
{
	int	i;

	i = 0;
	game->player.exit = 0;
	game->flo = 0;
	game->ceil = 0;
	game->no = 0;
	game->so = 0;
	game->ea = 0;
	game->we = 0;
	game->map_tex.no = NULL;
	game->map_tex.so = NULL;
	game->map_tex.ea = NULL;
	game->map_tex.we = NULL;
	game->mlx = mlx_init();
	while (i++ < 4)
		game->tex[i].img = NULL;
}

bool	init_game(t_game *game, char *av)
{
	char	**map;

	map = NULL;
	init_variables(game);
	game->map = read_map(av, map, game);
	if (game->map == NULL)
		return (false);
	find_player(game->map, &game->player);
	if (game->flo == 0 || game->ceil == 0)
		ft_putstr("Error: Missing C (ceiling) or F (floor) color in map.\n");
	if (game->player.exit == 1 || game->flo == 0 || game->ceil == 0)
		exit_error(game, 1, 1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (true);
}
