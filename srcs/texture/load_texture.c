/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:54:58 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/15 14:51:38 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	load_single_texture(t_game *game, int index, char *path)
{
	game->tex[index].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->tex[index].width, &game->tex[index].height);
	if (game->tex[index].img == NULL)
	{
		ft_putstr("Error: Cannot open with this texture: ");
		ft_putendl_fd(path, 1);
		exit_error(game, 3, 2);
	}
	game->tex[index].addr = mlx_get_data_addr(game->tex[index].img,
			&game->tex[index].bpp, &game->tex[index].line_len,
			&game->tex[index].endian);
}

void	load_all_textures(t_game *game)
{
	if (game->map_tex.no
		&& game->map_tex.so
		&& game->map_tex.ea
		&& game->map_tex.we)
	{
		load_single_texture(game, 0, game->map_tex.no);
		load_single_texture(game, 1, game->map_tex.so);
		load_single_texture(game, 3, game->map_tex.we);
		load_single_texture(game, 2, game->map_tex.ea);
	}
	else
	{
		ft_putstr("Need all the textures (NO, SO, EA, WE)");
		exit_error(game, 3, 1);
	}
}
