/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:14:49 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/08 16:55:10 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_move_handler(int x, int y, t_cub *cub)
{
	t_play	*player;
	int		delta_x;
	double	rot_speed;
	double	angle;
	double	old_x;

	if (cub->ignore_next_mouse)
	{
		cub->ignore_next_mouse = false;
		return (0);
	}
	player = &cub->player;
	rot_speed = 0.0025;
	delta_x = x - player->old_mouse_x;
	player->old_mouse_x = x;
	if (delta_x != 0)
	{
		angle = delta_x * rot_speed;
		old_x = player->dir[0];
		player->dir[0] = player->dir[0] * cos(angle)
			- player->dir[1] * sin(angle);
		player->dir[1] = old_x * sin(angle)
			+ player->dir[1] * cos(angle);
		old_x = player->cam[0];
		player->cam[0] = player->cam[0] * cos(angle)
			- player->cam[1] * sin(angle);
		player->cam[1] = old_x * sin(angle) + player->cam[1] * cos(angle);
		mlx_mouse_move(cub->mlx, cub->win, WIDTH / 2, HEIGHT / 2);
		cub->player.old_mouse_x = WIDTH / 2;
		cub->ignore_next_mouse = true;
	}
}
