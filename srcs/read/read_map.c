/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:46 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/16 15:43:29 by ratanaka         ###   ########.fr       */
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

static void	ft_after_map(int fd, t_game *game, t_mapstate st)
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

char	**read_map(const char *path, char **map, t_game *game)
{
	int			fd;
	t_mapstate	st;
	int			res;

	fd = open_map(path);
	if (fd < 0)
		return (NULL);
	st.map = map;
	st.count = 0;
	st.game = game;
	st.fd = fd;
	res = 1;
	while (res == 1)
		res = process_next_line(&st);
	if (st.map == NULL)
	{
		ft_printf("Empty map\n");
		exit_error(game, 0, 1);
	}
	ft_after_map(fd, game, st);
	close(fd);
	if (res == -1)
		return (NULL);
	if (is_map_closed(st.map) == 0)
	{
		ft_putstr("Error: something wrong in the map.\n");
		free_map(st.map);
		exit_error(game, 0, 1);
	}
	return (st.map);
}
