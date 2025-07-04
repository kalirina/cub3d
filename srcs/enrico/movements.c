/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:06:04 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/04 12:57:51 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	safe_exit(int data)
{
	exit(data);
}

int	key_pressed(int keycode, t_play *player)
{
	if (keycode == ESC)
		safe_exit(1);
	if (keycode == W)
		player->key_up = true;
	else if (keycode == S)
		player->key_down = true;
	else if (keycode == A)
		player->key_left = true;
	else if (keycode == D)
		player->key_right = true;
	else if (keycode == LEFT)
		player->left_rotate = true;
	else if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_released(int keycode, t_play	*player)
{
	if (keycode == W)
		player->key_up = false;
	else if (keycode == S)
		player->key_down = false;
	else if (keycode == A)
		player->key_left = false;
	else if (keycode == D)
		player->key_right = false;
	else if (keycode == LEFT)
		player->left_rotate = false;
	else if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move(t_play *player)
{
	double	speed;

	speed = 0.05;
	if (player->key_up)
	{
		player->x += player->dir[0] * speed;
		player->y += player->dir[1] * speed;
	}
	if (player->key_down)
	{
		player->x -= player->dir[0] * speed;
		player->y -= player->dir[1] * speed;
	}
	if (player->key_left)
	{
		player->x += player->dir[1] * speed;
		player->y -= player->dir[0] * speed;
	}
	if (player->key_right)
	{
		player->x -= player->dir[1] * speed;
		player->y += player->dir[0] * speed;
	}
}

//DA RISCRIVERE
// void	rotate(t_play *player)
// {
// 	double	old_dir_x;
// 	double	old_cam_x;
// 	double	rot_speed;
// 	double	angle;

// 	rot_speed = 0.025;
// 	if (player->left_rotate || player->right_rotate)
// 	{
// 		angle = player->right_rotate ? rot_speed : -rot_speed;
// 		old_dir_x = player->dir[0];
// 		old_cam_x = player->cam[0];
// 		player->dir[0] = player->dir[0] * cos(angle) 
//		- player->dir[1] * sin(angle);
// 		player->dir[1] = old_dir_x * sin(angle) 
//		+ player->dir[1] * cos(angle);
// 		player->cam[0] = player->cam[0] * cos(angle)
//		- player->cam[1] * sin(angle);
// 		player->cam[1] = old_cam_x * sin(angle) + player->cam[1] * cos(angle);
// 	}
// }

void	handle_movement(t_play *player)
{
	move(player);
}

// rotate(player);