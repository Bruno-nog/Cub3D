/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:48:27 by marvin            #+#    #+#             */
/*   Updated: 2025/09/28 18:48:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // Para malloc e exit
#include <stdio.h>  // Para printf (opcional, para debug)
// Inclua o header da MiniLibX (mlx.h) e o seu header (so_long.h, etc.) aqui.
#include "../includes/so_long.h"

// Suas funções (free_mlx, exit_game, keypress, game_start) permanecem as mesmas.
// ... (copie suas funções aqui ou garanta que elas estão no arquivo)

// A função 'exit_game' deve estar definida antes de ser usada no mlx_hook.

int exit_game(t_game *game)
{
    // ... seu código de limpeza
    if (game && game->mlx) // Verificação de segurança
    {
        // Se a MiniLibX for a versão que usa mlx_destroy_display:
        // mlx_destroy_display(game->mlx); 
        free(game->mlx); // Aqui liberamos a memória do mlx
    }
    if (game)
        free(game); // Liberamos a memória da estrutura t_game
    exit (0);
    return (0);
}

int	keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		exit_game(game);
	return (0);
}

void	game_start(t_game *game)
{
	game->mlx = mlx_init();
	// size_window_start(game);
	game->win = mlx_new_window(game->mlx, 1000, 1000, "so_long");
	// put_moves(game);
	game->endgame = 0;
	game->moves = 1;
	// start_image(game);
	// render_map(game);
}

int main()
{
    t_game  *game;

    // 1. ALOCAR MEMÓRIA PARA A ESTRUTURA t_game
    game = (t_game *)malloc(sizeof(t_game));
    if (!game)
    {
        perror("Erro na alocação de memória para game");
        return (1);
    }
    
    // 2. INICIAR O JOGO
    // Inicialize os campos importantes para evitar lixo de memória
    game->mlx = NULL;
    game->win = NULL;
    game_start(game); // Agora a função recebe um ponteiro válido

    // 3. ADICIONAR HOOKS
    // Note: O mlx_hook só deve ser chamado se game->win for válido
    if (game->win)
    {
        mlx_hook(game->win, 2, 1L << 0, keypress, game);
        mlx_hook(game->win, 17, 1L << 17, exit_game, game);
        mlx_loop(game->mlx);
    }
    else
    {
        // Se a janela não abrir (por mlx_new_window falhar), 
        // chamamos o exit_game para liberar a memória alocada.
        exit_game(game); 
    }
    
    return (0);
}


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
