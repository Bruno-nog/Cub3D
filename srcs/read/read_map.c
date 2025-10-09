/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:46 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/09 20:00:52 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static void	count_map(char **map, char **new_map, size_t *count)
{
	size_t	i;

	i = 0;
	while (i < *count)
	{
		new_map[i] = map[i];
		i++;
	}
}

static bool	verify_clean(char **map, char *clean, int fd)
{
	if (!clean)
	{
		perror("malloc/strdup");
		free_map(map);
		close(fd);
		return (false);
	}
	return (true);
}

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

char **read_map(const char *path, char **map, size_t count, char *line)
{
	int     fd;
	char    **new_map;
	char    *clean;

	fd = open_map(path);
	if (fd < 0)
		return NULL;
    while ((line = get_next_line(fd)))
    {
        clean = dup_line_no_newline(line);
        free(line);
		if (!verify_clean(map, clean, fd))
			return (NULL);
        new_map = malloc((count + 2) * sizeof(char *));
		if (!verify_map(map, new_map, clean, fd))
			return (NULL);
		count_map(map, new_map, &count);
        new_map[count] = clean;
        new_map[count + 1] = NULL;
        free(map);
        map = new_map;
        count++;
    }
    close(fd);
    return (map);
}
