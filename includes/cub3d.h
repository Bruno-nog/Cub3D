/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:21:37 by ratanaka          #+#    #+#             */
/*   Updated: 2025/09/29 15:16:11 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char	**mapcopy;
	char	**mapcopy2;
	int		row;
	int		colum;
	int		map_w;
	int		map_h;
	void	*img_backgroud;
	void	*img_wall;
	void	*img_player;
	void	*img_colect;
	void	*img_exit;
	void	*img_victory;
	int		img_w;
	int		img_h;
	int		img_victory_w;
	int		img_victory_h;
	int		n_colect;
	int		n_player;
	int		n_exit;
	int		x_player;
	int		y_player;
	int		moves;
	int		endgame;
}	t_game;

# define KEY_ESC 65307
# define KEY_Q 113

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

//MAP
void	read_map(t_game *game, char *path);
void	flood_fill(t_game *game, int move_x, int move_y);
void	flood_fill_2(t_game *game, int x, int y);
void	find_player_position(t_game *game, int *x, int *y);

//GRAPHIC
int		render_map(t_game *game);
void	game_start(t_game *game);

//GAME
void	move_player(t_game *game, int dx, int dy, char direction);
int		keypress(int keycode, t_game *game);
void	gameplay(t_game *game);
void	put_moves(t_game *game);

//FREE_EXIT
void	print_error(char	*str);
void	free_map(char **map);
int		exit_game(t_game *game);

//CHECKERS
int		map_checker(t_game *game);
int		validate_map(t_game *game);
int		validate_path(t_game *game);
int		map_checker_fill(t_game *game);
void	init_args(t_game *game);

#endif