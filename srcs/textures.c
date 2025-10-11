/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:01:47 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/11 17:23:36 by brunogue         ###   ########.fr       */
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
	if (game->map_tex.no
		&& game->map_tex.so
		&& game->map_tex.ea
		&& game->map_tex.we)
	{
		load_single_texture(game, 0, game->map_tex.no);
		load_single_texture(game, 1, game->map_tex.so);
		load_single_texture(game, 2, game->map_tex.ea);
		load_single_texture(game, 3, game->map_tex.we);
	}
	else
	{
		ft_putstr("Need all the textures (NO, SO, EA, WE)");
		free_map(game->map);
		exit(1);
	}
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

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

int	rgb_numbers(char *line, int	*floor_sky)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(line + 2, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if ((r > 255 || g > 255 || b > 255) || (r < 0 || g < 0 || b < 0))
	{
		ft_putstr("Error: RGB values must be between 0 and 255.\n");
		ft_free_split(split);
		exit(1);
	}
	*floor_sky = rgb_to_int(r, g, b);
	ft_free_split(split);
	return (1);
}

int	parse_textures(char *line, t_texture *tex)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		tex->no = ft_strdup(line + 3);
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		tex->so = ft_strdup(line + 3);
		return (1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		tex->we = ft_strdup(line + 3);
		return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		tex->ea = ft_strdup(line + 3);
		return (1);
	}
	if (ft_strncmp(line, "F ", 2) == 0)
		return (rgb_numbers(line, &tex->floor));
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (rgb_numbers(line, &tex->sky));
	return (0);
}
