/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:03:31 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/11 20:16:36 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_closed(char **map)
{
	int	rows;
	int	cols;
	int	i;
	int	j;

	rows = 0;
	cols = 0;
	j = 0;
	i = 0;
	while (map[rows])
		rows++;
	while(map[0][cols])
		cols++;
	while (j < cols)
	{
		if (map[0][j] != '1' || map[rows - 1][j] != '1')
			return (false);
		j++;
	}
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}