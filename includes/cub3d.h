/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:21:37 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/15 17:57:20 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       CUB3D.H      		                  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

/* --- Project Headers --- */
# include "struct.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

/* --- Standard Libraries --- */
# include <math.h>

/* --- Macros --- */
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
# define BLK 64
# define DEBUG 0
# define PLAYER_BUFFER 6.0f

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       PLAYER      		                  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

void			init_player(t_player *player);
void			player_move(t_player *player, double dt);
void			find_player(char **map, t_player *player);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_player *player);
void			find_player(char **map, t_player *player);

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       DRAW      		                 	  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

int				draw_loop(t_game *game, t_player *player);
void			draw_scene(t_game *game);
void			draw_square(int x, int y, int size, int color);
void			draw_vision(t_game *game, float ray_x, float ray_y, int i);
void			draw_map(t_game *game);
void			draw_line(t_player *player, t_game *game, float start_x, int i);
void			draw_wall_with_texture(t_game *game, t_drawparam *p);
unsigned int	get_texture_color(t_texture *texture, int x, int y);
void			correct_dist(t_game *game, t_rayinfo *ray,
					int tex_index, int i);

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       RAYCAST                               ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

bool			touch(float px, float py, t_game *game);
bool			init_game(t_game *game, char *av);
void			put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
float			fixed_dist(float y1, float x2, float y2, t_game *game);

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       READ	      		                  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

char			**read_map(const char *path, char **map,
					t_game *game);
int				open_map(const char *path);
void			count_map(char **map, char **new_map, size_t *count);
bool			verify_clean(char **map, char *clean, int fd);
char			*dup_line_no_newline(const char *s);
int				check_extra_after_map(int fd, int state, char *line);
int				encounter_directions(char *clean, int state);

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       TEXTURE	      		                  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

int				rgb_numbers(char *line, int	*floor_ceiling);
int				rgb_to_int(int r, int g, int b);
void			ft_free_split(char **split);
void			load_all_textures(t_game *game);

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       PARSER	      		                  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

bool			is_map_closed(char **map);
bool			main_parser(char *av);
int				parse_textures(char *line, t_texture *tex,
					t_game *game);
int				verify_directions(char *line);
void			north_direction(t_game *game, t_texture *tex, char *line);
void			south_direction(t_game *game, t_texture *tex, char *line);
void			west_direction(t_game *game, t_texture *tex, char *line);
void			east_direction(t_game *game, t_texture *tex, char *line);

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       VIGNETTE	   		                  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

int				darken_color(int color, float factor);
void			init_vignette(t_game *game);

/* ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *  ┃                       FREE		   		                  ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

int				exit_game(t_game *game);
void			free_map(char **map);
void			free_mlx(t_game *game);
void			free_vignette(t_game *game);
void			destroy_textures(t_game *game);
int				exit_game(t_game *game);
int				exit_error(t_game *game, int map, int map_text);

/* --- main --- */
t_global		*gg(void);

#endif