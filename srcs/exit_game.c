/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:51:04 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/10 15:26:51 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_mlx(t_game *game)
{
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	free_map(char **map)
{
	int i;

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

	if (!game->vignette_map)
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		free(game->vignette_map[y]);
		y++;
	}
	free(game->vignette_map);
}

void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i].img)
			mlx_destroy_image(game->mlx, game->texture[i].img);
		i++;
	}
}

int	exit_game(t_game *game)
{
	free_vignette(game);
	free_map(game->map);
	destroy_textures(game);
	if (game->img)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		free_mlx(game);
		game->mlx = NULL;
	}
	exit(0);
	return (0);
}
