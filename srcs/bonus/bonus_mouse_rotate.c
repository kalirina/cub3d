/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:14:49 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/10 17:20:14 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	mouse_move_handler(int x, int y, t_cub *cub)
{
	t_play	*player;
	int		delta_x;
	double	rot_speed;
	double	angle;
	double	old_x;

	player = &cub->player;
	rot_speed = 0.0025;
	delta_x = x - (WIDTH / 2);
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
	}
	return (0);
}
