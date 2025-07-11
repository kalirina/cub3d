/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:51 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/11 16:55:04 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

bool	is_door(char c)
{
	if (c == 'D' || c == 'O')
		return (true);
	return (false);
}

void	change_door_status(char *c)
{
	if (*c == 'D')
		*c = 'O';
	else if (*c == 'O')
		*c = 'D';
}

void	is_door_near(t_cub *cub, int door_y, int door_x)
{
	int	px;
	int	py;
	
	px = cub->player->x;
	py = cub->player->y;
	if (px == door_x)
	{
		if (py == door_y + 1 || py == door_y - 1)
			change_door_status(&cub->file.map[door_y][door_x]);
	}
	if (py == door_y)
	{
		if (px == door_x + 1 || px == door_x - 1)
			change_door_status(&cub->file.map[door_y][door_x]);
	}
}

void	open_door(t_cub *cub)
{
	int	x;
	int	y;
	
	y = 0;
	while (cub->file.map[y])
	{
		x = 0;
		while (cub->file.map[y][x])
		{
			if (is_door(cub->file.map[y][x]))
				is_door_near(cub, y, x);
			x++;
		}
		y++;
	}
}
