/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:21:33 by ratanaka          #+#    #+#             */
/*   Updated: 2025/04/11 21:23:10 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/so_long.h"

static int	is_rectangular(char **map)
{
	int	y;

	y = 0;
	if (!map)
		return (0);
	if (!map[y])
		return (0);
	while (map[y])
	{
		if (ft_strlen(map[y]) != ft_strlen(map[0]))
			return (0);
		y++;
	}
	if (y < 3)
		return (0);
	return (1);
}

static int	is_wall(char **map)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	x = 0;
	while (map[y])
		y++;
	while (map[0][x] && map[y - 1][x])
	{
		if (map[0][x] != '1' || map[y - 1][x] != '1')
			return (0);
		x++;
	}
	y = 1;
	len = ft_strlen(map[y]);
	while (map[y])
	{
		if (map[y][0] != '1' || map[y][len - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

static int	is_validate(t_game *game, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != 'E' && map[y][x] != 'C' && map[y][x] != 'P'
				&& map[y][x] != '0' && map[y][x] != '1')
				return (0);
			x++;
		}
	}
	if (map_checker_fill(game) == 0)
		return (0);
	return (1);
}

static int	is_ecp(t_game *game)
{
	int	y;
	int	x;

	game->n_colect = 0;
	game->n_player = 0;
	game->n_exit = 0;
	y = -1;
	while (game->map[++y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'E')
				game->n_exit++;
			if (game->map[y][x] == 'C')
				game->n_colect++;
			if (game->map[y][x] == 'P')
				game->n_player++;
			x++;
		}
	}
	if (game->n_exit == 0 || game->n_exit > 1
		|| game->n_colect == 0 || game->n_player != 1)
		return (0);
	return (1);
}

int	map_checker(t_game *game)
{
	int	i;

	init_args(game);
	if (is_rectangular(game->map))
	{
		game->colum = ft_strlen(game->map[0]);
		i = 0;
		while (game->map[i])
			i++;
		game->row = i;
		if (is_wall(game->map)
			&& is_validate(game, game->map) && is_ecp(game))
			return (1);
		return (0);
	}
	return (0);
}
