/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:01:47 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/15 16:34:05 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static bool	verify_floor_ceiling(char *line, t_texture *tex)
// {
// 	int	counter_f;
// 	int	counter_c;

// 	counter_f = 0;
// 	counter_c = 0;
// 	while (counter_f && counter_c)
// 	{
// 		if (ft_strncmp(line, "F ", 2) == 0)
// 		{
// 			counter_f++;
// 			return (rgb_numbers(line, &tex->floor));
// 		}
// 		else if (ft_strncmp(line, "C ", 2) == 0)
// 		{
// 			counter_c++;
// 			return (rgb_numbers(line, &tex->ceiling));
// 		}
// 		if ((counter_c == 0 || counter_f == 0) || (counter_c > 1 || counter_f > 1))
// 		{
// 			ft_printf("Have to contain floor and ceiling");
// 			return (false);
// 		}
// 		else
// 			return (true);
// 	}
// 	return (true);
// }



// int	parse_textures(char *line, t_texture *tex)
// {

// 	if (ft_strncmp(line, "NO ", 3) == 0)
// 	{
// 		tex->no = ft_strdup(line + 3);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "SO ", 3) == 0)
// 	{
// 		tex->so = ft_strdup(line + 3);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "WE ", 3) == 0)
// 	{
// 		tex->we = ft_strdup(line + 3);
// 		return (1);
// 	}
// 	else if (ft_strncmp(line, "EA ", 3) == 0)
// 	{
// 		tex->ea = ft_strdup(line + 3);
// 		return (1);
// 	}
// 	if (ft_strncmp(line, "F ", 2) == 0)
// 	{
// 		tex->count_f++;
// 		ft_printf("count floor\n");
// 		if (tex->count_f > 2)
// 		{
// 			ft_printf("count floor error\n");
// 			return (0);
// 		}
// 		return (rgb_numbers(line, &tex->floor));
// 	}
// 	else if (ft_strncmp(line, "C ", 2) == 0)
// 	{
// 		tex->count_c++;
// 		ft_printf("count ceiling\n");
// 		if (tex->count_c > 2)
// 		{
// 			ft_printf("count ceiling error\n");
// 			return (0);
// 		}
// 		return (rgb_numbers(line, &tex->ceiling));
// 	}
// 	return (0);
// }

int	rgb_checker(char *line, t_texture *tex, t_game *game)
{
	int	error;

	error = 0;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		game->flo++;
		error = rgb_numbers(line, &tex->floor);
		if (error == 2 || game->flo > 1)
		{
			free(line);
			exit_error(game, 0);
		}
		else
			return (error);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		game->ceil++;
		error = rgb_numbers(line, &tex->ceiling);
		if (error == 2 || game->ceil > 1)
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
