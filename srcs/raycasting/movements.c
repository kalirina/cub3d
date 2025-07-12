/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:06:04 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/12 11:35:12 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_pressed(int keycode, void *param)
{
	t_cub	*cub;
	t_play	*player;

	cub = (t_cub *)param;
	player = cub->player;
	if (keycode == ESC)
		safe_exit(cub);
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

int	key_released(int keycode, void *param)
{
	t_cub	*cub;
	t_play	*player;

	cub = (t_cub *)param;
	player = cub->player;
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

void	move(t_play *player, t_cub *cub)
{
	if (player->key_up)
	{
		proceed_move(cub, player, player->x + player->dir[0] * MOVE_SPEED, \
			player->y + player->dir[1] * MOVE_SPEED);
	}
	if (player->key_down)
	{
		proceed_move(cub, player, player->x - player->dir[0] * MOVE_SPEED, \
			player->y - player->dir[1] * MOVE_SPEED);
	}
	if (player->key_left)
	{
		proceed_move(cub, player, player->x + player->dir[1] * MOVE_SPEED, \
			player->y - player->dir[0] * MOVE_SPEED);
	}
	if (player->key_right)
	{
		proceed_move(cub, player, player->x - player->dir[1] * MOVE_SPEED, \
			player->y + player->dir[0] * MOVE_SPEED);
	}
}

void	rotate(t_play *player)
{
	double	tmp_x;
	double	angle;

	if (player->left_rotate || player->right_rotate)
	{
		if (player->right_rotate)
			angle = ROT_KEY_SPEED;
		else if (player->left_rotate)
			angle = -ROT_KEY_SPEED;
		tmp_x = player->dir[0];
		player->dir[0] = player->dir[0] * cos(angle)
			- player->dir[1] * sin(angle);
		player->dir[1] = tmp_x * sin(angle)
			+ player->dir[1] * cos(angle);
		tmp_x = player->cam[0];
		player->cam[0] = player->cam[0] * cos(angle)
			- player->cam[1] * sin(angle);
		player->cam[1] = tmp_x * sin(angle) + player->cam[1] * cos(angle);
	}
}

void	handle_movement(t_play *player, t_cub *cub)
{
	move(player, cub);
	rotate(player);
}
