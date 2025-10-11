/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:46 by brunogue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/10 17:42:16 by ratanaka         ###   ########.fr       */
=======
/*   Updated: 2025/10/10 14:05:36 by brunogue         ###   ########.fr       */
>>>>>>> ff86ffa3e1c27bb2c226cbfc8e3db902b38d4433
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

char	**read_map(const char *path, char **map, size_t count, char *line, t_game *game)
{
	int		fd;
	char	**new_map;
	char	*clean;

	fd = open_map(path);
	if (fd < 0)
<<<<<<< HEAD
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		clean = dup_line_no_newline(line);
		free(line);
		if (!verify_clean(map, clean, fd))
			return (NULL);
		if (!parse_textures(clean, &game->map_tex) && clean[0] != '\0')
		{
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
		else
			free(clean);
	}
	close(fd);
	return (map);
=======
		return NULL;
	line = get_next_line(fd);
    while (line != NULL)
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
		line = get_next_line(fd);
    }
    close(fd);
    return (map);
>>>>>>> ff86ffa3e1c27bb2c226cbfc8e3db902b38d4433
}
