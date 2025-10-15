/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratanaka <ratanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:49:08 by brunogue          #+#    #+#             */
/*   Updated: 2025/10/15 17:02:40 by ratanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;

	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		count_f;
	int		count_c;
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	left_rotate;
	bool	right_rotate;

	int		column;
	int		row;

	int		exit;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_texture	tex[4];
	float		**vig_map;
	char		**map;
	t_player	player;
	t_texture	map_tex;

	int			flo;
	int			ceil;
	int			no;
	int			so;
	int			we;
	int			ea;
}	t_game;

typedef struct s_global
{
	float	x1;
	char	**map;
	t_game	game;
}	t_global;

typedef struct s_move
{
	float	speed;
	float	angle_speed;
	float	ds;
	float	da;
	float	cos_angle;
	float	sin_angle;
}	t_move;

typedef struct s_vec
{
	float	x;
	float	y;
}	t_vec;

typedef struct s_pos
{
	int	row;
	int	col;
}	t_pos;

typedef struct s_rayinfo
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
}	t_rayinfo;

typedef struct s_mapstate
{
	char	**map;
	size_t	count;
	t_game	*game;
	int		fd;
}	t_mapstate;

typedef struct s_drawparams
{
	int		screen_x;
	float	height;
	int		tex_index;
	float	wall_x;
}	t_drawparam;

#endif