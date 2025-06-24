/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:06:04 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/24 16:48:33 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	key_pressed(int keycode, t_player *player)
{
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

int	key_released(int keycode, t_player	*player)
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

void	move(t_player *player, float cos, float sin)
{
	int		speed;

	speed = 3;
	if (player->key_up)
    {
        player->x += cos * speed;
        player->y += sin * speed;
    }
    if (player->key_down)
    {
        player->x -= cos * speed;
        player->y -= sin * speed;
    }
    if (player->key_left)
    {
        player->x += sin * speed;
        player->y -= cos * speed;
    }
    if (player->key_right)
    {
        player->x -= sin * speed;
        player->y += cos * speed;
    }
}

void	rotate(t_player *player)
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

void	handle_movement(t_player *player)
{
	float cos_angle;
	float sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move(player, cos_angle, sin_angle);
	rotate(player);
}