/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:01:47 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/06 13:27:52 by ratanaka         ###   ########.fr       */
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

// void	draw_wall_simple(t_game *game, int screen_x, float ray_x, float ray_y, int color)
// {
// 	float	dist;
// 	float	height;
// 	int		start_y;
// 	int		end_y;

// 	start_y = (HEIGHT - height) / 2;
// 	dist = fixed_dist(game->player.y, ray_x, ray_y, game);
// 	height = (BLOCK / dist) * (WIDTH / 2);
// 	end_y = start_y + height;
// 	while (start_y < end_y)
// 	{
// 		put_pixel(screen_x, start_y, color, game);
// 		start_y++;
// 	}
// }

// void	draw_line(t_player *player, t_game *game, float start_x, int i)
// {
// 	float	cos_angle;
// 	float	sin_angle;
// 	float	ray_x;
// 	float	ray_y;
// 	int		side;

// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);
// 	ray_x = player->x;
// 	ray_y = player->y;
// 	while (!touch(ray_x, ray_y, game))
// 	{
// 		if (DEBUG)
// 			put_pixel(ray_x, ray_y, 0xFF0000, game);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	if ((int)((ray_x - cos_angle) / BLOCK) != (int)(ray_x / BLOCK))
// 		side = 1;
// 	else
// 		side = 0;
// 	if (!DEBUG)
// 		draw_vision(game, ray_x, ray_y, i);
// }
