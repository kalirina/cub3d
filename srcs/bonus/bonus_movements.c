/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:55:51 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/10 17:20:18 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	safe_exit(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->img)
		mlx_destroy_image(cub->mlx, cub->img);
	if (cub->min.img)
		mlx_destroy_image(cub->mlx, cub->min.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	free_all(cub);
	exit(0);
}

int	key_pressed(int keycode, void *param)
{
	t_cub	*cub;
	t_play	*player;

	cub = (t_cub *)param;
	player = &cub->player;
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
	player = &cub->player;
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

void	rotate(t_play *player)
{
	double	tmp_x;
	double	rot_speed;
	double	angle;

	rot_speed = 0.025;
	if (player->left_rotate || player->right_rotate)
	{
		if (player->right_rotate)
			angle = rot_speed;
		else if (player->left_rotate)
			angle = -rot_speed;
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

void	handle_movement_bonus(t_play *player, t_cub *cub)
{
	move_bonus(player, cub);
	rotate(player);
}
