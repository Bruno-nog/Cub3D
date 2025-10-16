/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:01:47 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/16 15:26:08 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error_f(char *line, t_game *game)
{
	free(line);
	if (game->flo > 1)
		ft_putstr("Error: Multiple Floor (F) definitions found\n");
	exit_error(game, 0, 1);
}

static void	error_c(char *line, t_game *game)
{
	free(line);
	if (game->ceil > 1)
		ft_putstr("Error: Multiple Ceiling (C) definitions found\n");
	exit_error(game, 0, 1);
}

int	rgb_checker(char *line, t_texture *tex, t_game *game)
{
	int	error;

	error = 0;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		game->flo++;
		error = rgb_numbers(line, &tex->floor);
		if (error == 2 || game->flo > 1)
			error_f(line, game);
		else
			return (error);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		game->ceil++;
		error = rgb_numbers(line, &tex->ceiling);
		if (error == 2 || game->ceil > 1)
			error_c(line, game);
		else
			return (error);
	}
	else if (line == (void *)0)
		free(line);
	return (error);
}

int	parse_textures(char *line, t_texture *tex, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		north_direction(game, tex, line);
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		south_direction(game, tex, line);
		return (1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		west_direction(game, tex, line);
		return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		east_direction(game, tex, line);
		return (1);
	}
	return (rgb_checker(line, tex, game));
}

int	verify_directions(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}
