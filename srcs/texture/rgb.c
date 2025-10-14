/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:59:16 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/14 15:47:12 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	rgb_numbers(char *line, int	*floor_ceiling)
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
		free(line);
		return (2);
	}
	*floor_ceiling = rgb_to_int(r, g, b);
	ft_free_split(split);
	return (1);
}
