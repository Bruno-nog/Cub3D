/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:01:47 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/13 14:11:15 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (rgb_numbers(line, &tex->ceiling));
	return (0);
}
