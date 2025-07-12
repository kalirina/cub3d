/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_raycasting_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 09:14:55 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/12 11:45:58 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

double	find_wall_x(t_dda *data, t_play *player)
{
	double	wall_x;

	if (data->side == 0)
	data->perp_dist = (data->map_cord[0] - player->x
				+ (1 - data->step[0]) / 2)
			/ data->ray_dir[0];
	else
	data->perp_dist = (data->map_cord[1] - player->y
				+ (1 - data->step[1]) / 2)
			/ data->ray_dir[1];
	if (data->side == 1)
		wall_x = player->x + data->perp_dist * data->ray_dir[0];
	else
		wall_x = player->y + data->perp_dist * data->ray_dir[1];
	wall_x -= floor(wall_x);
	return (wall_x);
}

t_door	*find_door(t_cub *cub, int x, int y)
{
	t_door	*d;
	int		i;

	i = 0;
	while (i < cub->n_doors)
	{
		d = cub->doors[i];
		if (d->x == x && d->y == y)
			return (d);
		i++;
	}
	return (NULL);
}

bool	is_door_open(t_cub *cub, t_dda *data)
{
	double	wall_x;
	t_door	*d;

	d = find_door(cub, data->map_cord[0], data->map_cord[1]);
	if (!d)
		return (false);
	wall_x = find_wall_x(data, cub->player);
	if (wall_x < d->progress)
		return (false);
	else
		return (true);
}
