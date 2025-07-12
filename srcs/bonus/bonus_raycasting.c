/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:47:58 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/10 13:44:43 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_side(t_cub *cub, t_dda *data)
{
	if (data->side == 1 && data->ray_dir[1] > 0)
	{
		data->wall_type = 'N';
		data->texture_index = 0;
	}
	else if (data->side == 1 && data->ray_dir[1] < 0)
	{
		data->wall_type = 'S';
		data->texture_index = 1;
	}
	else if (data->side == 0 && data->ray_dir[0] > 0)
	{
		data->wall_type = 'W';
		data->texture_index = 2;
	}
	else if (data->side == 0 && data->ray_dir[0] < 0)
	{
		data->wall_type = 'E';
		data->texture_index = 3;
	}
}

void	dda(t_cub *cub, t_dda *data, bool hit)
{
	while (!hit)
	{
		if (data->side_dist[0] < data->side_dist[1])
		{
			data->side_dist[0] += data->delta[0];
			data->map_cord[0] += (int) data->step[0];
			data->side = 0;
		}
		else
		{
			data->side_dist[1] += data->delta[1];
			data->map_cord[1] += (int) data->step[1];
			data->side = 1;
		}
		if (cub->file.map[data->map_cord[1]][data->map_cord[0]] == '1')
			hit = true;
		if (cub->file.map[data->map_cord[1]][data->map_cord[0]] == 'D')
		{
			if (!is_door_open(cub, data))
				hit = true;
		}
	}
	check_side(cub, data);
}

void	find_step(t_play *player, t_dda *data)
{
	if (data->ray_dir[0] < 0)
	{
		data->step[0] = -1;
		data->side_dist[0] = (player->x - data->map_cord[0]) * data->delta[0];
	}
	else
	{
		data->step[0] = 1;
		data->side_dist[0] = (data->map_cord[0] + 1.0
				- player->x) * data->delta[0];
	}
	if (data->ray_dir[1] < 0)
	{
		data->step[1] = -1;
		data->side_dist[1] = (player->y - data->map_cord[1]) * data->delta[1];
	}
	else
	{
		data->step[1] = 1;
		data->side_dist[1] = (data->map_cord[1] + 1.0
				- player->y) * data->delta[1];
	}
}

void	config_dda(t_play *player, t_dda *data)
{
	int		map_cord[2];
	double	delta[2];
	int		step[2];

	data->map_cord[0] = (int) floor(player->x);
	data->map_cord[1] = (int) floor(player->y);
	data->delta[0] = fabs(1 / data->ray_dir[0]);
	data->delta[1] = fabs(1 / data->ray_dir[1]);
	find_step(player, data);
}

void	raycasting(t_play *player, t_cub *cub)
{
	t_dda	data;
	int		x;
	double	line_height;

	init_dda(&data);
	x = 0;
	while (x < WIDTH)
	{
		data.cam_pos = ((2 * x) / (double) WIDTH) - 1;
		data.ray_dir[0] = player->dir[0] + (player->cam[0] * data.cam_pos);
		data.ray_dir[1] = player->dir[1] + (player->cam[1] * data.cam_pos);
		config_dda(player, &data);
		dda(cub, &data, false);
		data.line_height = get_line_height(&data, player);
		add_line_to_img(cub, &data, x, find_texture_x(&data, cub->player));
		x++;
	}
}
