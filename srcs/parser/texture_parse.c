/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:01:47 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/13 16:03:17 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_checker(char *line, t_texture *tex, t_game *game)
{
	int	error;

	error = 0;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		error = rgb_numbers(line, &tex->floor);
		if (error == 2)
		{
			free(line);
			exit_error(game, 0);
		}
		else
			return (error);
	}
	else if (ft_strncmp(line, "S ", 2) == 0)
	{
		error = rgb_numbers(line, &tex->sky);
		if (error == 2)
		{
			free(line);
			exit_error(game, 0);
		}
		else
			return (error);
	}
	return (error);
}

int	parse_textures(char *line, t_texture *tex, t_game *game)
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
	return (rgb_checker(line, tex, game));
}
