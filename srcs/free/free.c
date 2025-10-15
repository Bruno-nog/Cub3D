/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:34:55 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/15 16:35:18 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mlx(t_game *game)
{
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_vignette(t_game *game)
{
	int	y;

	if (!game->vig_map)
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		free(game->vig_map[y]);
		y++;
	}
	free(game->vig_map);
}
