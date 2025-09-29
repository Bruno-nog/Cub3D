/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:31:31 by ratanaka          #+#    #+#             */
/*   Updated: 2025/04/14 11:27:02 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/so_long.h"

void	flood_fill_2(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->row || y >= game->colum)
		return ;
	if (game->mapcopy2[x][y] == 'E')
		game->mapcopy2[x][y] = '1';
	if (game->mapcopy2[x][y] == '1' || game->mapcopy2[x][y] == 'X')
		return ;
	game->mapcopy2[x][y] = 'X';
	flood_fill_2(game, x + 1, y);
	flood_fill_2(game, x - 1, y);
	flood_fill_2(game, x, y + 1);
	flood_fill_2(game, x, y - 1);
}

int	validate_path(t_game *game)
{
	int	i;
	int	valid;

	if (!game->mapcopy2)
		return (0);
	flood_fill_2(game, game->x_player, game->y_player);
	i = -1;
	valid = 1;
	while (game->mapcopy2[++i])
	{
		if (ft_strchr(game->mapcopy2[i], 'C'))
		{
			valid = 0;
			break ;
		}
	}
	return (valid);
}

int	map_checker_fill(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	find_player_position(game, &x, &y);
	flood_fill_2(game, x, y);
	if (validate_path(game) == 0)
		return (0);
	x = 0;
	y = 0;
	find_player_position(game, &x, &y);
	flood_fill(game, x, y);
	if (validate_map(game) == 0)
		return (0);
	return (1);
}
