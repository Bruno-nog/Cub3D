/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:56:01 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/15 17:58:55 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north_direction(t_game *game, t_texture *tex, char *line)
{
	game->no++;
	if (game->no == 1)
		tex->no = ft_strdup(line + 3);
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
		tex->so = ft_strdup(line + 3);
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
		tex->we = ft_strdup(line + 3);
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
		tex->ea = ft_strdup(line + 3);
	else
	{
		free(line);
		ft_putstr("Error: Multiple EA definitions found\n");
		exit_error(game, 0, 0);
	}
}
