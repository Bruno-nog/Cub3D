/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:21:37 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/10 21:12:58 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include <math.h>
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
void		move_player(t_player *player, double dt);
void		draw_scene(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_player *player);
int			exit_game(t_game *game);
bool		init_game(t_game *game, char *av);

int			parse_textures(char *line, t_texture *tex);
void		find_player(char **map, t_player *player);

void		draw_square(int x, int y, int size, int color);
void		draw_map(t_game *game);
void		draw_vision(t_game *game, float ray_x, float ray_y, int i);
void		draw_line(t_player *player, t_game *game, float start_x, int i);
void		clear_image(t_game *game);
void		put_pixel(int x, int y, int color, t_game *game);
float		fixed_dist(float y1, float x2, float y2, t_game *game);
bool		touch(float px, float py, t_game *game);
bool		main_parser(char *av);
void		load_all_textures(t_game *game);
void		free_vignette(t_game *game);

// GRAPHIC

// RAYCAST


// READ
char		**read_map(const char *path, char **map,
			size_t count, char *line, t_game *game);


// UTILS_READ
char		*dup_line_no_newline(const char *s);
void		free_map(char **map);


// VIGNETTE

int			darken_color(int color, float factor);
void		init_vignette(t_game *game);


// EXIT_GAME

void		free_map(char **map);
void		free_vignette(t_game *game);
void		destroy_textures(t_game *game);
int			exit_game(t_game *game);


#endif