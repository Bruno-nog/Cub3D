/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:56:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/16 14:10:52 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*value_from_line(const char *line)
{
	int			i;
	const char	*start;
	int			len;

	i = 0;
	while (line[i] && ft_isalpha((unsigned char)line[i]))
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = line + i;
	len = 0;
	while (start[len] && start[len] != '\n')
		len++;
	while (len > 0 && (start[len - 1] == ' ' || start[len - 1] == '\t'))
		len--;
	return (ft_substr(start, 0, len));
}

void	north_direction(t_game *game, t_texture *tex, char *line)
{
	game->no++;
	if (game->no == 1)
		tex->no = value_from_line(line);
	else
	{
		free(line);
		ft_putstr("Error: Multiple NO definitions found\n");
		exit_error(game, 0, 0);
	}
}

void	south_direction(t_game *game, t_texture *tex, char *line)
{
	game->so++;
	if (game->so == 1)
		tex->so = value_from_line(line);
	else
	{
		free(line);
		ft_putstr("Error: Multiple SO definitions found\n");
		exit_error(game, 0, 0);
	}
}

void	west_direction(t_game *game, t_texture *tex, char *line)
{
	game->we++;
	if (game->we == 1)
		tex->we = value_from_line(line);
	else
	{
		free(line);
		ft_putstr("Error: Multiple WE definitions found\n");
		exit_error(game, 0, 0);
	}
}

void	east_direction(t_game *game, t_texture *tex, char *line)
{
	game->ea++;
	if (game->ea == 1)
		tex->ea = value_from_line(line);
	else
	{
		free(line);
		ft_putstr("Error: Multiple EA definitions found\n");
		exit_error(game, 0, 0);
	}
}
