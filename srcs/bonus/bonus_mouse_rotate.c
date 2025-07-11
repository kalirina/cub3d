/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:14:49 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/11 17:03:11 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	mouse_move_handler(int x, int y, t_cub *cub)
{
	t_play	*player;
	int		delta_x;
	double	angle;
	double	old_x;

	player = &cub->player;
	delta_x = x - (WIDTH / 2);
	if (delta_x != 0)
	{
		angle = delta_x * ROT_MOUS_SPEED;
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
