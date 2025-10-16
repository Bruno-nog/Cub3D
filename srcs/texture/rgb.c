/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:59:16 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/16 17:06:59 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_to_value(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isalpha((unsigned char)line[i]))
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

static int	is_valid_rgb_token(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i] == '+')
		i++;
	if (!s[i] || !ft_isdigit((unsigned char)s[i]))
		return (0);
	while (s[i] && ft_isdigit((unsigned char)s[i]))
		i++;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	return (s[i] == '\0');
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static int	rgb_errors_type(int type_error, char **split)
{
	if (type_error == 1)
	{
		ft_putstr("Error: RGB values must be between 0 and 255.\n");
		ft_free_split(split);
		return (2);
	}
	else if (type_error == 2)
	{
		ft_putstr("Error: Floor or Ceiling color ");
		ft_putstr("must have exactly 3 values (R,G,B).\n");
		ft_free_split(split);
		return (2);
	}
	else if (type_error == 3)
	{
		ft_putstr("Error: RGB values must be numbers.\n");
		ft_free_split(split);
		return (2);
	}
	ft_putstr("Error: No values for Floor or Ceiling.\n");
	ft_free_split(split);
	return (2);
}

int	rgb_numbers(char *line, int	*floor_ceiling)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	int		count;

	count = 0;
	split = ft_split(skip_to_value(line), ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (rgb_errors_type(0, split));
	while (split[count])
		count++;
	if (count != 3)
		return (rgb_errors_type(2, split));
	if (!is_valid_rgb_token(split[0]) || !is_valid_rgb_token(split[1])
		|| !is_valid_rgb_token(split[2]))
		return (rgb_errors_type(3, split));
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if ((r > 255 || g > 255 || b > 255) || (r < 0 || g < 0 || b < 0))
		return (rgb_errors_type(1, split));
	*floor_ceiling = rgb_to_int(r, g, b);
	ft_free_split(split);
	return (1);
}
