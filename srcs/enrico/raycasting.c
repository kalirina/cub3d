/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:47:58 by enrmarti          #+#    #+#             */
/*   Updated: 2025/06/30 19:03:01 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_line_height(t_dda *data, t_play *player)
{
	double	perp_dist;
	int		line_height;

	if (data->side == 0)
		perp_dist = (data->map_cord[0] - player->x + (1 - data->step[0]) /2) / data->ray_dir[0];	
	else
		perp_dist = (data->map_cord[1] - player->y + (1 - data->step[1]) /2) / data->ray_dir[1];	
	line_height = (int) (HEIGHT / perp_dist);
}

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
			data->map_cord[0] += data->step[0];
			data->side = 0;
		}
		else
		{
			data->side_dist[1] += data->delta[1];
			data->map_cord[1] += data->step[1];
			data->side = 1;
		}
		if (cub->file.map[data->map_cord[0]][data->map_cord[1]] == '1')
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
		data->side_dist[0] = (data->map_cord[0] + 1.0 - player->x) * data->delta[0];
	}
	if (data->ray_dir[1] < 0)
	{
		data->step[1] = -1;
		data->side_dist[1] = (player->x - data->map_cord[1]) * data->delta[1];
	}
	else
	{
		data->step[1] = 1;
		data->side_dist[1] = (data->map_cord[1] + 1.0 - player->x) * data->delta[1];
	}
}

void	config_dda(t_play *player, t_dda *data)
{
	int		map_cord[2];
	double	delta[2];
	int		step[2];

	data->map_cord[0] = (int) player->x;
	data->map_cord[1] = (int) player->y;
	data->delta[0] = fabs(1 / data->ray_dir[0]);
	data->delta[1] = fabs(1 / data->ray_dir[1]);
	find_step(player, &data);
}

void	raycasting(t_play *player, t_cub *cub)
{
	t_dda	data;
	int		x;
	// double	ray_pos[2];

	x = 0;
	// ray_pos[0] = player->x;
	// ray_pos[1] = player->y;
	while (x < WIDTH)
	{
		data.cam_pos = (2 * x) / (double) WIDTH - 1;
		data.ray_dir[0] = player->dir[0] + (player->cam[0] * data.cam_pos);
		data.ray_dir[1] = player->dir[1] + (player->cam[1] * data.cam_pos);
		config_dda(player, &data);
		dda(cub, &data);
		
		// distance();
		// draw(distance, cam_pos)
		x++;
	}
}
