/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:26:44 by brunogue          #+#    #+#             */
/*   Updated: 2025/09/29 15:26:44 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include "mlx.h"

int exit_game(t_game *game)
{
    if (!game)
        exit(0);
    if (game->mlx && game->win)
    {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
    }
    free(game);
    exit(0);
    return (0);
}

int keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC || keycode == KEY_Q)
        exit_game(game);
    return (0);
}

int keyrelease(int keycode, t_game *game)
{
    (void)keycode;
    (void)game;
    return (0);
}

// int render_frame(t_game *game)
// {
//     (void)game;
//     return (0);
// }

void game_start(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        perror("Erro: mlx_init falhou");
        free(game);
        exit(1);
    }
    game->win = mlx_new_window(game->mlx, 1000, 1000, "Cub3D");
    if (!game->win)
    {
        perror("Erro: mlx_new_window falhou");
        free(game);
        exit(1);
    }
    game->endgame = 0;
    game->moves = 1;
}



#ifndef WIN_W
# define WIN_W 1000
#endif
#ifndef WIN_H
# define WIN_H 1000
#endif

#define MINIMAP_SCALE 12
#define MINIMAP_PAD 10
#define PLAYER_RAD 3
#define DIR_LINE_LEN 20

static void put_pixel(char *data, int x, int y, int line_len, int bpp, int color)
{
    int bytes = bpp / 8;
    char *dst;

    if (x < 0 || y < 0)
        return;
    dst = data + y * line_len + x * bytes;
    if (bytes == 4)
        *(unsigned int *)dst = (unsigned int)color;
    else if (bytes == 3)
    {
        dst[0] = (color) & 0xFF;
        dst[1] = (color >> 8) & 0xFF;
        dst[2] = (color >> 16) & 0xFF;
    }
}

static void draw_rect(char *data, int x0, int y0, int w, int h, int line_len, int bpp, int color)
{
    int x, y;

    for (y = 0; y < h; ++y)
        for (x = 0; x < w; ++x)
            put_pixel(data, x0 + x, y0 + y, line_len, bpp, color);
}

/* Bresenham simples para desenhar linha (usado para direção do jogador) */
static void draw_line(char *data, int x0, int y0, int x1, int y1, int line_len, int bpp, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        put_pixel(data, x0, y0, line_len, bpp, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}



int render_frame(t_game *game)
{
    void    *img;
    char    *data;
    int     bpp;
    int     line_len;
    int     endian;
    int     ceil_color = 0x333333;
    int     floor_color = 0x777777;
    int     wall_color = 0xFFFFFF;
    int     floor_map_color = 0x000000;
    int     player_color = 0xFF0000;
    int     dir_color = 0x00FF00;
    int     i, j;
    int     map_px_w, map_px_h;
    int     map_draw_x = MINIMAP_PAD;
    int     map_draw_y = MINIMAP_PAD;
    int     px, py;
    int     dir_x = 0, dir_y = 0;
    int     dir_px, dir_py;

    if (!game || !game->mlx || !game->win)
        return (0);

    img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    if (!img)
        return (0);
    data = mlx_get_data_addr(img, &bpp, &line_len, &endian);

    /* céu e chão */
    draw_rect(data, 0, 0, WIN_W, WIN_H / 2, line_len, bpp, ceil_color);
    draw_rect(data, 0, WIN_H / 2, WIN_W, WIN_H - (WIN_H / 2), line_len, bpp, floor_color);

    /* minimapa */
    if (game->map && game->map_width > 0 && game->map_height > 0)
    {
        map_px_w = game->map_width * MINIMAP_SCALE;
        map_px_h = game->map_height * MINIMAP_SCALE;

        /* fundo do minimapa */
        draw_rect(data, map_draw_x - 2, map_draw_y - 2, map_px_w + 4, map_px_h + 4, line_len, bpp, 0x222222);

        for (i = 0; i < game->map_height; ++i)
        {
            for (j = 0; j < game->map_width; ++j)
            {
                char c = game->map[i][j];
                int color = floor_map_color;
                if (c == '1')
                    color = wall_color;
                draw_rect(data, map_draw_x + j * MINIMAP_SCALE, map_draw_y + i * MINIMAP_SCALE,
                          MINIMAP_SCALE, MINIMAP_SCALE, line_len, bpp, color);
            }
        }

        /* jogador */
        px = (int)(map_draw_x + (game->player_x * MINIMAP_SCALE));
        py = (int)(map_draw_y + (game->player_y * MINIMAP_SCALE));
        for (i = -PLAYER_RAD; i <= PLAYER_RAD; ++i)
            for (j = -PLAYER_RAD; j <= PLAYER_RAD; ++j)
                if (i * i + j * j <= PLAYER_RAD * PLAYER_RAD)
                    put_pixel(data, px + j, py + i, line_len, bpp, player_color);

        /* linha de direção simples baseada em player_dir (N/S/E/W) */
        if (game->player_dir == 'N') { dir_x = 0; dir_y = -1; }
        else if (game->player_dir == 'S') { dir_x = 0; dir_y = 1; }
        else if (game->player_dir == 'E') { dir_x = 1; dir_y = 0; }
        else if (game->player_dir == 'W') { dir_x = -1; dir_y = 0; }

        dir_px = px + dir_x * DIR_LINE_LEN;
        dir_py = py + dir_y * DIR_LINE_LEN;
        draw_line(data, px, py, dir_px, dir_py, line_len, bpp, dir_color);
    }

    mlx_put_image_to_window(game->mlx, game->win, img, 0, 0);
    mlx_destroy_image(game->mlx, img);

    return (0);
}

int main(int ac, char **av)
{
    t_game  *game;

    if (ac != 2)
    {
        fprintf(stderr, "Usage: %s map.cub\n", av[0]);
        return (1);
    }

    game = malloc(sizeof(t_game));
    if (!game)
    {
        perror("Erro na alocação de memória para game");
        return (1);
    }
    /* inicializa ponteiros e valores padrão */
    game->mlx = NULL;
    game->win = NULL;
    game->map = NULL;
    game->map_width = 0;
    game->map_height = 0;
    game->player_x = 0.0;
    game->player_y = 0.0;
    game->player_dir = '\0';
    game->endgame = 0;
    game->moves = 0;

    /* Lê e valida o mapa ANTES de iniciar o MLX */
    read_map(game, av[1]);

    /* agora que o mapa e player estão prontos, iniciar MLX/janela */
    game_start(game);

    mlx_hook(game->win, 2, 1L << 0, keypress, game);
    mlx_hook(game->win, 3, 1L << 1, keyrelease, game);
    mlx_hook(game->win, 17, 0L, (int (*)(void *))exit_game, game);
    mlx_loop_hook(game->mlx, render_frame, game);
    mlx_loop(game->mlx);

    return (0);
}



// int exit_game(t_game *game)
// {
//     if (game && game->mlx)
//         free(game->mlx);
//     if (game)
//         free(game);
//     exit (0);
//     return (0);
// }

// int	keypress(int keycode, t_game *game)
// {
// 	if (keycode == KEY_ESC || keycode == KEY_Q)
// 		exit_game(game);
// 	return (0);
// }

// void	game_start(t_game *game)
// {
// 	game->mlx = mlx_init();
// 	game->win = mlx_new_window(game->mlx, 1000, 1000, "Cub3D");
// 	game->endgame = 0;
// 	game->moves = 1;
// }

// int main()
// {
//     t_game  *game;

//     game = (t_game *)malloc(sizeof(t_game));
//     if (!game)
//     {
//         perror("Erro na alocação de memória para game");
//         return (1);
//     }
//     game->mlx = NULL;
//     game->win = NULL;
//     game_start(game);
//     if (game->win)
//     {
//         mlx_hook(game->win, 2, 1L << 0, keypress, game);
//         mlx_hook(game->win, 17, 1L << 17, exit_game, game);
//         mlx_loop(game->mlx);
//     }
//     else
//         exit_game(game); 
//     return (0);
// }


// #include <stdio.h>
// #include "../includes/so_long.h"

// // static void	size_window_start(t_game *game)
// // {
// // 	int	i;

// // 	game->map_w = ft_strlen(game->map[0]) * 32;
// // 	i = 0;
// // 	while (game->map[i])
// // 		i++;
// // 	game->map_h = i * 32;
// // }
// static void	free_mlx(t_game *game)
// {
// 	mlx_destroy_display(game->mlx);
// 	free(game->mlx);
// }


// int	exit_game(t_game *game)
// {
// 	// if (game->map)
// 	// 	free_map(game->map);
// 	// if (game->mapcopy)
// 	// 	free_map(game->mapcopy);
// 	// if (game->mapcopy2)
// 	// 	free_map(game->mapcopy2);
// 	// if (game->img_backgroud)
// 	// 	mlx_destroy_image(game->mlx, game->img_backgroud);
// 	// if (game->img_wall)
// 	// 	mlx_destroy_image(game->mlx, game->img_wall);
// 	// if (game->img_player)
// 	// 	mlx_destroy_image(game->mlx, game->img_player);
// 	// if (game->img_colect)
// 	// 	mlx_destroy_image(game->mlx, game->img_colect);
// 	// if (game->img_exit)
// 	// 	mlx_destroy_image(game->mlx, game->img_exit);
// 	// if (game->img_victory)
// 	// 	mlx_destroy_image(game->mlx, game->img_victory);
// 	// if (game->win)
// 	// 	mlx_destroy_window(game->mlx, game->win);
// 	if (game->mlx)
// 		free_mlx(game);
// 	exit (0);
// 	return (0);
// }

// int	keypress(int keycode, t_game *game)
// {
// 	if (keycode == KEY_ESC || keycode == KEY_Q)
// 		exit_game(game);
// 	return (0);
// }

// void	game_start(t_game *game)
// {
// 	game->mlx = mlx_init();
// 	// size_window_start(game);
// 	game->win = mlx_new_window(game->mlx, 1000, 1000, "so_long");
// 	// put_moves(game);
// 	game->endgame = 0;
// 	game->moves = 1;
// 	// start_image(game);
// 	// render_map(game);
// }

// int main ()
// {
// 	t_game	*game;
// 	game = NULL;

// 	game_start(game);
// 	mlx_hook(game->win, 2, 1L << 0, keypress, game);
// 	mlx_hook(game->win, 17, 1L << 17, exit_game, game);
// 	mlx_loop(game->mlx);
// }
