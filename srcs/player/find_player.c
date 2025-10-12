/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:56:41 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/12 18:56:54 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	counter_player(int *player_count)
{
	if (*player_count > 1)
	{
		ft_putstr("Error: More than one player on the map.\n");
		return (false);
	}
	if (*player_count == 0)
	{
		ft_putstr("Error: No player found on the map.\n");
		return (false);
	}
	return (true);
}

static void	handle_player_at(char **map, t_player *player,
				t_pos *pos, int *player_count)
{
	char	c;

	c = map[pos->row][pos->col];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		*player_count = *player_count + 1;
		if (counter_player(player_count) == 0)
			exit(1);
		player->row = pos->row;
		player->column = pos->col;
		player->x = pos->col * BLK + BLK / 2;
		player->y = pos->row * BLK + BLK / 2;
		map[pos->row][pos->col] = '0';
	}
}

void	find_player(char **map, t_player *player)
{
	int		row;
	int		col;
	int		player_count;
	t_pos	pos;

	player_count = 0;
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			pos.row = row;
			pos.col = col;
			handle_player_at(map, player, &pos, &player_count);
			col++;
		}
		row++;
	}
	if (counter_player(&player_count) == 0)
		exit(1);
}
