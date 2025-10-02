/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2025/10/01 17:43:08 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/01 18:41:47 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

static char *dup_line_no_newline(const char *s)
{
    size_t len = ft_strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        len--;
    char *copy = malloc(len + 1);
    if (!copy)
        return NULL;
    ft_memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

char **read_map(const char *path)
{
    int     fd;
    char    *line;
    char    **map = NULL;
    size_t  count = 0;
    char    **tmp;
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
            // free_map(map);
            close(fd);
            return NULL;
        }
        tmp = realloc(map, sizeof(char *) * (count + 2));
        if (!tmp)
        {
            perror("realloc");
            free(clean);
            // free_map(map);
            close(fd);
            return NULL;
        }
        map = tmp;
        map[count++] = clean;
        map[count] = NULL;
    }
    close(fd);
    return map;
}

void	init_game(t_game *game, char *av)
{
	game->mlx = mlx_init();
	game->map = read_map(av);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}
