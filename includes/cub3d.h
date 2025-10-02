/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:21:37 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/02 12:21:05 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define KEY_ESC 65307
# define PI 3.14159265359

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

t_global	*gg(void);
void		init_player(t_player *player);
void		move_player(t_player *player);
int			key_press(int keycode, t_player *player);
int			key_release(int keycode, t_player *player);
char 		**read_map(const char *path);
int			exit_game(t_game *game);
void		init_game(t_game *game, char *av);

void		draw_square(int x, int y, int size, int color);
void		draw_map(t_game *game);
void		draw_vision(t_game *game, float ray_x, float ray_y, int i);
void		draw_line(t_player *player, t_game *game, float start_x, int i);
void		clear_image(t_game *game);
void		put_pixel(int x, int y, int color, t_game *game);
float		fixed_dist(float y1, float x2, float y2, t_game *game);
bool		touch(float px, float py, t_game *game);
bool	    main_parser(char *av);

// GRAPHIC

// RAYCAST



#endif