/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:01:47 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/09 14:29:58 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

static void	load_single_texture(t_game *game, int index, char *path)
{
	game->texture[index].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->texture[index].width, &game->texture[index].height);
	if (game->texture[index].img == NULL)
	{
		printf("Erro: Não foi possível carregar a textura: %s\n", path);
		exit(1);
	}
	game->texture[index].addr = mlx_get_data_addr(game->texture[index].img,
			&game->texture[index].bpp, &game->texture[index].line_len,
			&game->texture[index].endian);
}

void	load_all_textures(t_game *game)
{
	load_single_texture(game, 0, "texture/north.xpm");
	load_single_texture(game, 1, "texture/south.xpm");
	load_single_texture(game, 2, "texture/east.xpm");
	load_single_texture(game, 3, "texture/west.xpm");
}
