/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:27:09 by brunogue          #+#    #+#             */
/*   Updated: 2025/09/30 16:54:06 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* read_map.c */
/* read_map.c */
#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int is_blank_line(char *s)
{
    int i = 0;
    if (!s)
        return (1);
    while (s[i])
    {
        if (s[i] != ' ' && s[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

/* reconhece linhas de configuração no cabeçalho: "NO ", "SO ", "WE ", "EA ", "F ", "C " */
static int is_config_line(char *s)
{
    int i = 0;
    if (!s)
        return (0);
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    if (!s[i])
        return (0);
    if (s[i] == 'N' && s[i+1] == 'O' && (s[i+2] == ' ' || s[i+2] == '\t'))
        return (1);
    if (s[i] == 'S' && s[i+1] == 'O' && (s[i+2] == ' ' || s[i+2] == '\t'))
        return (1);
    if (s[i] == 'W' && s[i+1] == 'E' && (s[i+2] == ' ' || s[i+2] == '\t'))
        return (1);
    if (s[i] == 'E' && s[i+1] == 'A' && (s[i+2] == ' ' || s[i+2] == '\t'))
        return (1);
    if ((s[i] == 'F' || s[i] == 'C') && (s[i+1] == ' ' || s[i+1] == '\t'))
        return (1);
    return (0);
}


void read_map(t_game *game, char *path)
{
    int fd;
    char *line;
    char *holder;
    char *tmp;
    char **rows;
    int total_rows;
    int start;
    int i, j;
    int player_found;

    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo de mapa");
        exit(EXIT_FAILURE);
    }
    holder = ft_strdup("");
    while ((line = get_next_line(fd)))
    {
        tmp = holder;
        holder = ft_strjoin(holder, line);
        free(tmp);
        free(line);
    }
    close(fd);

    rows = ft_split(holder, '\n');
    free(holder);
    if (!rows)
    {
        fprintf(stderr, "Erro ao processar arquivo de mapa\n");
        exit(EXIT_FAILURE);
    }

    /* contar linhas totais */
    total_rows = 0;
    while (rows[total_rows])
        total_rows++;

    /* encontrar começo do bloco de mapa: pula configuração e linhas em branco iniciais */
    start = 0;
    while (start < total_rows && (is_blank_line(rows[start]) || is_config_line(rows[start])))
        start++;

    if (start >= total_rows)
    {
        fprintf(stderr, "Arquivo não contém bloco de mapa\n");
        exit(EXIT_FAILURE);
    }

    /* agora copiamos o bloco de mapa: parar se encontrarmos uma linha em branco após começar o mapa */
    {
        int idx = start;
        int map_len = 0;
        while (idx < total_rows && !is_blank_line(rows[idx]))
        {
            map_len++;
            idx++;
        }

        /* aloca um novo array contendo apenas as linhas do mapa */
        char **map_rows = malloc((map_len + 1) * sizeof(char *));
        if (!map_rows)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < map_len; ++i)
            map_rows[i] = rows[start + i];
        map_rows[map_len] = NULL;
        /* liberamos as linhas que ficaram antes e depois (apenas o array 'rows' sem as strings copiadas) */
        for (i = 0; i < start; ++i)
            free(rows[i]);
        for (i = start + map_len; i < total_rows; ++i)
            free(rows[i]);
        free(rows);
        rows = map_rows;
        total_rows = map_len;
    }

    /* compute width/height: width = maior comprimento */
    game->map_height = total_rows;
    game->map_width = 0;
    for (i = 0; i < game->map_height; ++i)
    {
        int len = (int)ft_strlen(rows[i]);
        if (len > game->map_width)
            game->map_width = len;
    }

    /* pad lines to same width with spaces */
    for (i = 0; i < game->map_height; ++i)
    {
        int len = (int)ft_strlen(rows[i]);
        if (len < game->map_width)
        {
            char *padded = malloc(game->map_width + 1);
            int k = 0;
            while (k < game->map_width)
            {
                if (k < len)
                    padded[k] = rows[i][k];
                else
                    padded[k] = ' ';
                k++;
            }
            padded[k] = '\0';
            free(rows[i]);
            rows[i] = padded;
        }
    }

    /* valida caracteres e encontra player */
    player_found = 0;
    for (i = 0; i < game->map_height; ++i)
    {
        for (j = 0; j < game->map_width; ++j)
        {
            char c = rows[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                player_found = 1;
                game->player_x = j + 0.5;
                game->player_y = i + 0.5;
                game->player_dir = c;
                rows[i][j] = '0'; /* torna caminhável no mapa interno */
            }
        }
    }

    game->map = rows;
}


// void	read_map(t_game *game, char *path)
// {
// 	int		fd;
// 	char	*line;
// 	char	*holder_map;
// 	char	*holder_old;

// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		printf("File error or empty");
// 	holder_map = ft_strdup("");
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		holder_old = holder_map;
// 		holder_map = ft_strjoin(holder_old, line);
// 		free(line);
// 		free(holder_old);
// 	}
// 	game->map = ft_split(holder_map, '\n');
// 	game->mapcopy = ft_split(holder_map, '\n');
// 	game->mapcopy2 = ft_split(holder_map, '\n');
// 	free(holder_map);
// 	close(fd);
// }

// void	flood_fill(t_game *game, int move_x, int move_y)
// {
// 	if (move_x < 0 || move_y < 0 || move_x >= game->row
// 		|| move_y >= game->colum || game->mapcopy[move_x][move_y] == '1'
// 		|| game->mapcopy[move_x][move_y] == 'X')
// 		return ;
// 	game->mapcopy[move_x][move_y] = 'X';
// 	flood_fill(game, move_x - 1, move_y);
// 	flood_fill(game, move_x + 1, move_y);
// 	flood_fill(game, move_x, move_y - 1);
// 	flood_fill(game, move_x, move_y + 1);
// }

// void	find_player_position(t_game *game, int *x, int *y)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < game->row)
// 	{
// 		j = 0;
// 		while (j < game->colum)
// 		{
// 			if (game->map[i][j] == 'P')
// 			{
// 				*x = i;
// 				*y = j;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int	validate_map(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < game->row)
// 	{
// 		j = 0;
// 		while (j < game->colum)
// 		{
// 			if ((game->map[i][j] == 'C' || game->map[i][j] == 'E')
// 				&& game->mapcopy[i][j] != 'X')
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// void	init_args(t_game *game)
// {
// 	game->row = 0;
// 	game->colum = 0;
// 	game->x_player = 0;
// 	game->y_player = 0;
// }
