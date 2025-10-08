/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:53:52 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/08 16:13:52 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

static void	player_angle(t_player *player,
	float cos_angle, float sin_angle, float speed)
{
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		player->x += sin_angle * (speed);
		player->y -= cos_angle * (speed);
	}
	if (player->key_right)
	{
		player->x -= sin_angle * (speed);
		player->y += cos_angle * (speed);
	}
}

void	draw_scene(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	clear_image(game);
	if (DEBUG)
	{
		draw_square(player->x, player->y, 10, 0x00FF00);
		draw_map(game);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	move_player(t_player *player, double dt)
{
	float	speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;
	double	ds;
	double	da;

	speed = 200.0f;
	angle_speed = 2.05f;

	ds = (double)speed * dt; da = (double)angle_speed * dt;
	cos_angle = cos(player->angle); sin_angle = sin(player->angle);
	if (player->left_rotate == true)
		player->angle -= (float)da;
	if (player->right_rotate == true)
		player->angle += (float)da;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
	player_angle(player, cos_angle, sin_angle, (float)ds);
}


// void	move_player(t_player *player)
// {
// 	float	speed;
// 	float	angle_speed;
// 	float	cos_angle;
// 	float	sin_angle;

// 	speed = 3;
// 	angle_speed = 0.05;
// 	cos_angle = cos(player->angle);
// 	sin_angle = sin(player->angle);
// 	if (player->left_rotate)
// 		player->angle -= angle_speed;
// 	if (player->right_rotate)
// 		player->angle += angle_speed;
// 	if (player->angle > 2 * PI)
// 		player->angle = 0;
// 	if (player->angle < 0)
// 		player->angle = 2 * PI;
// 	player_angle(player, cos_angle, sin_angle, speed);
// }
