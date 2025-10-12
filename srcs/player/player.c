/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunogue <brunogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:53:52 by ratanaka          #+#    #+#             */
/*   Updated: 2025/10/12 18:56:35 by brunogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>


static void	try_move_x(t_player *player, float dx)
{
	float	nx;
	float	test;

	nx = player->x + dx;
	if (dx > 0.0f)
		test = nx + PLAYER_BUFFER;
	else
		test = nx - PLAYER_BUFFER;
	if (touch(test, player->y, &gg()->game) == false)
		player->x = nx;
}

static void	try_move_y(t_player *player, float dy)
{
	float	ny;
	float	test;

	ny = player->y + dy;
	if (dy > 0.0f)
		test = ny + PLAYER_BUFFER;
	else
		test = ny - PLAYER_BUFFER;
	if (touch(player->x, test, &gg()->game) == false)
		player->y = ny;
}

static t_vec	player_angle_lateral(t_player *player,
	float cos_angle, float sin_angle, float speed)
{
	t_vec	res;

	res.x = 0.0f;
	res.y = 0.0f;
	if (player->key_right)
	{
		res.x += -sin_angle * (speed / 2.5f);
		res.y +=  cos_angle * (speed / 2.5f);
	}
	if (player->key_left)
	{
		res.x +=  sin_angle * (speed / 2.5f);
		res.y += -cos_angle * (speed / 2.5f);
	}
	return (res);
}

static void	player_angle(t_player *player,
	float cos_angle, float sin_angle, float speed)
{
	t_vec	lateral;
	float	dx;
	float	dy;

	dx = 0.0f;
	dy = 0.0f;
	if (player->key_up)
	{
		dx += cos_angle * speed;
		dy += sin_angle * speed;
	}
	if (player->key_down)
	{
		dx -= cos_angle * speed;
		dy -= sin_angle * speed;
	}
	lateral = player_angle_lateral(player, cos_angle, sin_angle, speed);
	dx += lateral.x;
	dy += lateral.y;
	if (dx == 0.0f && dy == 0.0f)
		return ;
	try_move_x(player, dx);
	try_move_y(player, dy);
}

void move_player(t_player *player, double dt)
{
    t_move m;

    m.speed = 200.0f;
    m.angle_speed = 1.55f;
    m.ds = m.speed * (float)dt;
    m.da = m.angle_speed * (float)dt;
    m.cos_angle = cos(player->angle);
    m.sin_angle = sin(player->angle);
    if (player->left_rotate)
        player->angle -= m.da;
    if (player->right_rotate)
        player->angle += m.da;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;
    player_angle(player, m.cos_angle, m.sin_angle, m.ds);
}
