/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:06:04 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/30 13:37:53 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	safe_exit(int data)
{
	//free
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
	int speed;

	speed = 5;
	if (player->key_up)
         player->y -= speed;
    if (player->key_down)
        player->y += speed;
    if (player->key_left)
        player->x -= speed;
    if (player->key_right)
        player->x += speed;
	// float cos_angle = cos(player->angle);
    // float sin_angle = sin(player->angle);
	// if (player->key_up)
    // {
    //     player->x += cos_angle * speed;
    //     player->y += sin_angle * speed;
    // }
    // if (player->key_down)
    // {
    //     player->x -= cos_angle * speed;
    //     player->y -= sin_angle * speed;
    // }
    // if (player->key_left)
    // {
    //     player->x += sin_angle * speed;
    //     player->y -= cos_angle * speed;
    // }
    // if (player->key_right)
    // {
    //     player->x -= sin_angle * speed;
    //     player->y += cos_angle * speed;
    // }
}

void	rotate(t_play *player)
{
	float	rotation_speed;

	rotation_speed = 0.03;
	if (player->left_rotate)
        player->angle -= rotation_speed;
    if (player->right_rotate)
        player->angle += rotation_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
}

void	handle_movement(t_play *player)
{
	move(player);
	rotate(player);
}
