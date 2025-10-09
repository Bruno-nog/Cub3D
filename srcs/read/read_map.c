/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:46 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/09 17:23:47 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *dup_line_no_newline(const char *s)
{
    size_t	orig_len;
    size_t	len;
    char	*copy;

    if (!s)
        return NULL;
    orig_len = ft_strlen(s);
    len = orig_len;
    if (len > 0 && s[len - 1] == '\n')
        len--;
    copy = malloc(len + 1);
    if (!copy)
        return NULL;
    if (len > 0)
        ft_memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}


static void free_map(char **map)
{
    size_t i;

    if (!map)
        return;
    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

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
char **read_map(const char *path)
{
    int     fd;
    char    *line;
    char    **map = NULL;
    size_t  count = 0;
    char    **new_map;
    char    *clean;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return NULL;
    }
    while ((line = get_next_line(fd)))
    {
        clean = dup_line_no_newline(line);
        free(line);
        if (!clean)
        {
            perror("malloc/strdup");
            free_map(map);
            close(fd);
            return NULL;
        }
        new_map = malloc((count + 2) * sizeof(char *));
        if (!new_map)
        {
            perror("malloc");
            free(clean);
            free_map(map);
            close(fd);
            return NULL;
        }
		count_map(map, new_map, &count);
        new_map[count] = clean;
        new_map[count + 1] = NULL;
        free(map);
        map = new_map;
        count++;
    }
    close(fd);
    return map;
}
