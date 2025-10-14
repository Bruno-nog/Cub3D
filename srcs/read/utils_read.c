/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:18:37 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/14 19:43:28 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_map(char **map, char **new_map, size_t *count)
{
	size_t	i;

	i = 0;
	while (i < *count)
	{
		new_map[i] = map[i];
		i++;
	}
}

bool	verify_clean(char **map, char *clean, int fd)
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

char	*dup_line_no_newline(const char *s)
{
	size_t	orig_len;
	size_t	len;
	char	*copy;

	if (!s)
		return (NULL);
	orig_len = ft_strlen(s);
	len = orig_len;
	if (len > 0 && s[len - 1] == '\n')
		len--;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	if (len > 0)
		ft_memcpy(copy, s, len);
	copy[len] = '\0';
	return (copy);
}
