/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:24:19 by ratanaka          #+#    #+#             */
/*   Updated: 2025/09/29 15:14:26 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_game *game, char *path)
{
	int		fd;
	char	*line;
	char	*holder_map;
	char	*holder_old;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_error("File error or empty");
	holder_map = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		holder_old = holder_map;
		holder_map = ft_strjoin(holder_old, line);
		free(line);
		free(holder_old);
	}
	game->map = ft_split(holder_map, '\n');
	game->mapcopy = ft_split(holder_map, '\n');
	game->mapcopy2 = ft_split(holder_map, '\n');
	free(holder_map);
	close(fd);
}

void	flood_fill(t_game *game, int move_x, int move_y)
{
	if (move_x < 0 || move_y < 0 || move_x >= game->row
		|| move_y >= game->colum || game->mapcopy[move_x][move_y] == '1'
		|| game->mapcopy[move_x][move_y] == 'X')
		return ;
	game->mapcopy[move_x][move_y] = 'X';
	flood_fill(game, move_x - 1, move_y);
	flood_fill(game, move_x + 1, move_y);
	flood_fill(game, move_x, move_y - 1);
	flood_fill(game, move_x, move_y + 1);
}

void	find_player_position(t_game *game, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->row)
	{
		j = 0;
		while (j < game->colum)
		{
			if (game->map[i][j] == 'P')
			{
				*x = i;
				*y = j;
			}
			j++;
		}
		i++;
	}
}

int	validate_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->row)
	{
		j = 0;
		while (j < game->colum)
		{
			if ((game->map[i][j] == 'C' || game->map[i][j] == 'E')
				&& game->mapcopy[i][j] != 'X')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	init_args(t_game *game)
{
	game->row = 0;
	game->colum = 0;
	game->x_player = 0;
	game->y_player = 0;
}
