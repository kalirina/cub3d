/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_wall_coll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:44:46 by irkalini          #+#    #+#             */
/*   Updated: 2025/07/12 10:23:50 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

bool	is_walkable(char c)
{
	if (c == '1' || c == 'D')
		return (false);
	return (true);
}

void	move_bonus(t_play *player, t_cub *cub)
{
	double	next_x;
	double	next_y;

	if (player->key_up)
	{
		next_x = player->x + player->dir[0] * MOVE_SPEED;
		next_y = player->y + player->dir[1] * MOVE_SPEED;
		if (is_walkable(cub->file.map[(int)next_y][(int)player->x]))
			player->y = next_y;
		if (is_walkable(cub->file.map[(int)player->y][(int)next_x]))
			player->x = next_x;
	}
	if (player->key_down)
	{
		next_x = player->x - player->dir[0] * MOVE_SPEED;
		next_y = player->y - player->dir[1] * MOVE_SPEED;
		if (is_walkable(cub->file.map[(int)next_y][(int)player->x]))
			player->y = next_y;
		if (is_walkable(cub->file.map[(int)player->y][(int)next_x]))
			player->x = next_x;
	}
	if (player->key_left)
		move_left_right(player, cub, 0);
	if (player->key_right)
		move_left_right(player, cub, 1);
}

void	move_left_right(t_play *player, t_cub *cub, int key)
{
	double	next_x;
	double	next_y;

	if (key == 0)
	{
		next_x = player->x + player->dir[1] * MOVE_SPEED;
		next_y = player->y - player->dir[0] * MOVE_SPEED;
		if (is_walkable(cub->file.map[(int)next_y][(int)player->x]))
			player->y = next_y;
		if (is_walkable(cub->file.map[(int)player->y][(int)next_x]))
			player->x = next_x;
	}
	else
	{
		next_x = player->x - player->dir[1] * MOVE_SPEED;
		next_y = player->y + player->dir[0] * MOVE_SPEED;
		if (is_walkable(cub->file.map[(int)next_y][(int)player->x]))
			player->y = next_y;
		if (is_walkable(cub->file.map[(int)player->y][(int)next_x]))
			player->x = next_x;
	}
}
