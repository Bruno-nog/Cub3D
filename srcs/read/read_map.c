/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:46 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/16 17:59:34 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

static bool	verify_map(char **map, char **new_map, char *clean, int fd)
{
	if (!new_map)
	{
		perror("malloc");
		free(clean);
		free_map(map);
		close(fd);
		return (false);
	}
	return (true);
}

static char	**append_map_line(char **map, char *clean, size_t *count, int fd)
{
	char	**new_map;

	new_map = malloc((*count + 2) * sizeof(char *));
	if (new_map == NULL)
		return (NULL);
	if (verify_map(map, new_map, clean, fd) == 0)
	{
		free(new_map);
		return (NULL);
	}
	count_map(map, new_map, count);
	new_map[*count] = clean;
	new_map[*count + 1] = NULL;
	free(map);
	*count = *count + 1;
	return (new_map);
}

static int	process_next_line(t_mapstate *st)
{
	char	*line;
	char	*clean;

	line = get_next_line(st->fd);
	if (line == NULL)
		return (0);
	clean = dup_line_no_newline(line);
	free(line);
	if (verify_clean(st->map, clean, st->fd) == 0)
	{
		free(clean);
		return (-1);
	}
	if (parse_textures(clean, &st->game->map_tex, st->game) == 0
		&& clean[0] != '\0')
	{
		st->map = append_map_line(st->map, clean, &st->count, st->fd);
		if (st->map == NULL)
			return (-1);
	}
	else
		free(clean);
	return (1);
}

static int	process_and_validate(t_mapstate *st, int fd, t_game *game)
{
	int	res;

	res = 1;
	while (res == 1)
		res = process_next_line(st);
	ft_after_map(fd, game, *st);
	if (st->map == NULL)
	{
		ft_putstr("Empty map\n");
		exit_error(game, 0, 1);
		return (-1);
	}
	close(fd);
	if (res == -1)
		return (-1);
	if (is_map_closed(st->map) == 0)
	{
		ft_putstr("Error: something wrong in the map.\n");
		free_map(st->map);
		exit_error(game, 0, 1);
		return (-1);
	}
	return (0);
}

char	**read_map(const char *path, char **map, t_game *game)
{
	int			fd;
	t_mapstate	st;

	fd = open_map(path);
	if (fd < 0)
	{
		return (NULL);
	}
	st.map = map;
	st.count = 0;
	st.game = game;
	st.fd = fd;
	if (process_and_validate(&st, fd, game) == -1)
	{
		return (NULL);
	}
	return (st.map);
}
