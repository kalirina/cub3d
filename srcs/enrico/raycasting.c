/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:47:58 by enrmarti          #+#    #+#             */
/*   Updated: 2025/07/04 13:01:22 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_side(t_dda *data)
{
	if (data->side == 0)
	{
		if (data->ray_dir[0] > 0)
			data->wall_type = 'W';
		else
			data->wall_type = 'E';
	}
	else
	{
		if (data->ray_dir[1] > 0)
			data->wall_type = 'N';
		else
			data->wall_type = 'S';
	}
}

void	dda(t_cub *cub, t_dda *data)
{
	bool	hit;

	hit = false;
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
	}
	check_side(data);
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

	x = 0;
	while (x < WIDTH)
	{
		data.cam_pos = ((2 * x) / (double) WIDTH) - 1;
		data.ray_dir[0] = player->dir[0] + (player->cam[0] * data.cam_pos);
		data.ray_dir[1] = player->dir[1] + (player->cam[1] * data.cam_pos);
		config_dda(player, &data);
		dda(cub, &data);
		line_height = get_line_height(&data, player);
		add_line_to_img(cub, &data, line_height, x);
		x++;
	}
}
