/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:24:27 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/16 15:35:39 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	encounter_map_color(char *clean, int state, int j)
{
	while (clean[j] == ' ')
		j++;
	while (1)
	{
		if (clean[j] == '1' || clean[j] == '0' || clean[j] == 'N'
			|| clean[j] == 'S' || clean[j] == 'E' || clean[j] == 'W')
		{
			if (state == 2)
			{
				free(clean);
				return (-1);
			}
			state = 1;
			free(clean);
			continue ;
		}
		if (state == 1)
		{
			free(clean);
			return (-1);
		}
	}
	return (0);
}

int	encounter_directions(char *clean, int state)
{
	while (1)
	{
		if (verify_directions(clean) == 1)
		{
			if (state == 1 || state == 2)
			{
				free(clean);
				return (-1);
			}
			free(clean);
			continue ;
		}
	}
	return (0);
}

int	check_extra_after_map(int fd, int state, char *line)
{
	char	*clean;
	int		j;

	j = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		clean = dup_line_no_newline(line);
		free(line);
		if (clean[0] == '\0')
		{
			if (state == 1)
				state = 2;
			free(clean);
			continue ;
		}
		if (encounter_directions(clean, state) == -1)
			return (-1);
		if (encounter_map_color(clean, state, j) == -1)
			return (-1);
		free(clean);
	}
	return (0);
}

void	ft_after_map(int fd, t_game *game, t_mapstate st)
{
	int		after_map;
	int		state;
	char	*line;

	state = 0;
	line = NULL;
	after_map = check_extra_after_map(fd, state, line);
	if (after_map != 0)
	{
		ft_putstr("Error: extra content after map.\n");
		free_map(st.map);
		exit_error(game, 0, 1);
	}
}
