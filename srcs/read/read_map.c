/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:46 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/16 20:49:09 by brunogue         ###   ########.fr       */
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

char *trim_copy(const char *s)
{
    int start;
    int end;
    int len;
    char *out;
    int i;

    if (s == NULL)
        return (NULL);
    start = 0;
    while (s[start] == ' ' || s[start] == '\t')
        start++;
    len = 0;
    while (s[start + len])
        len++;
    if (len == 0)
    {
        out = malloc(1);
        if (out == NULL)
            return (NULL);
        out[0] = '\0';
        return (out);
    }
    end = start + len - 1;
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r'))
        end--;
    i = 0;
    out = malloc((end - start + 2));
    if (out == NULL)
        return (NULL);
    while (start <= end)
    {
        out[i++] = s[start++];
    }
    out[i] = '\0';
    return (out);
}

static int process_next_line(t_mapstate *st)
{
    char    *line;
    char    *clean;
    char    *trimmed;

    line = get_next_line(st->fd);
    if (line == NULL)
        return (0);
    clean = dup_line_no_newline(line);
    free(line);
    trimmed = trim_copy(clean);
    free(clean);
    if (trimmed == NULL)
    {
        perror("malloc");
        return (-1);
    }
    if (verify_clean(st->map, trimmed, st->fd) == 0)
    {
        free(trimmed);
        return (-1);
    }
    if (parse_textures(trimmed, &st->game->map_tex, st->game) == 0
        && trimmed[0] != '\0')
    {
        st->map = append_map_line(st->map, trimmed, &st->count, st->fd);
        if (st->map == NULL)
            return (-1);
    }
    else
        free(trimmed);
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
		ft_printf("Empty map\n");
		exit_error(game, 0 , 1);
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
