/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:46 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/14 18:20:08 by brunogue         ###   ########.fr       */
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

static int	open_map(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
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

int	check_extra_after_map(const char *path, t_game *game)
{
	(void)game;
	int		fd;
	char	*line;
	char	*clean;
	int		state;
	int		j;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-2);
	}
	state = 0;
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
		if (verify_directions(clean) == 1)
		{
			if (state == 1 || state == 2)
			{
				free(clean);
				close(fd);
				return (-1);
			}
			free(clean);
			continue ;
		}
		j = 0;
		while (clean[j] == ' ')
			j++;
		if (clean[j] == '1' || clean[j] == '0' || clean[j] == 'N'
			|| clean[j] == 'S' || clean[j] == 'E' || clean[j] == 'W')
		{
			if (state == 2)
			{
				free(clean);
				close(fd);
				return (-1);
			}
			state = 1;
			free(clean);
			continue ;
		}
		if (state == 1)
		{
			free(clean);
			close(fd);
			return (-1);
		}
		free(clean);
	}
	close(fd);
	return (0);
}


static void	ft_after_map(const char *path, t_game *game, t_mapstate st)
{
	int	after_map;

	after_map = check_extra_after_map(path, game);
	if (after_map != 0)
	{
		ft_putstr("Error: extra content after map.\n");
		free_map(st.map);
		exit_error(game, 0);
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
	close(fd);
	if (res == -1)
		return (NULL);
	ft_after_map(path, game, st);
	if (is_map_closed(st.map) == 0)
	{
		ft_putstr("Error: something wrong in the map.\n");
		free_map(st.map);
		exit_error(game, 0);
	}
	return (st.map);
}


// char	**read_map(const char *path, char **map, char *line, t_game *game)
// {
// 	int			fd;
// 	t_mapstate	st;
// 	int			res;

// 	(void)line;
// 	fd = open_map(path);
// 	if (fd < 0)
// 		return (NULL);
// 	st.map = map;
// 	st.count = 0;
// 	st.game = game;
// 	st.fd = fd;
// 	res = 1;
// 	while (res == 1)
// 		res = process_next_line(&st);
// 	close(fd);
// 	if (res == -1)
// 		return (NULL);
// 	if (is_map_closed(st.map) == 0)
// 	{
// 		ft_putstr("Error: Map is not closed by walls.\n");
// 		free_map(st.map);
// 		exit_error(game, 0);
// 	}
// 	return (st.map);
// }
