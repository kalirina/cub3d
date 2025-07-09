/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_wall_coll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:46 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/09 13:58:47 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_bonus(t_play *player, t_cub *cub)
{
	double	next_x;
	double	next_y;

	if (player->key_up)
	{
		next_x = player->x + player->dir[0] * player->move_speed;
		next_y = player->y + player->dir[1] * player->move_speed;
		if (cub->file.map[(int)next_y][(int)player->x] != '1')
			player->y = next_y;
		if (cub->file.map[(int)player->y][(int)next_x] != '1')
			player->x = next_x;
	}
	if (player->key_down)
	{
		next_x = player->x - player->dir[0] * player->move_speed;
		next_y = player->y - player->dir[1] * player->move_speed;
		if (cub->file.map[(int)next_y][(int)player->x] != '1')
			player->y = next_y;
		if (cub->file.map[(int)player->y][(int)next_x] != '1')
			player->x = next_x;
	}
	if (player->key_left)
		move_left_right(player, cub, 0, player->move_speed);
	if (player->key_right)
		move_left_right(player, cub, 1, player->move_speed);
}

void	move_left_right(t_play *player, t_cub *cub, int key, double speed)
{
	double	next_x;
	double	next_y;

	if (key == 0)
	{
		next_x = player->x + player->dir[1] * speed;
		next_y = player->y - player->dir[0] * speed;
		if (cub->file.map[(int)next_y][(int)player->x] != '1')
			player->y = next_y;
		if (cub->file.map[(int)player->y][(int)next_x] != '1')
			player->x = next_x;
	}
	else
	{
		next_x = player->x - player->dir[1] * speed;
		next_y = player->y + player->dir[0] * speed;
		if (cub->file.map[(int)next_y][(int)player->x] != '1')
			player->y = next_y;
		if (cub->file.map[(int)player->y][(int)next_x] != '1')
			player->x = next_x;
	}
}
